package com.example.thymeleafDemo.Controller;

import com.example.thymeleafDemo.Model.Device;
import com.example.thymeleafDemo.Model.Sensor;
import com.example.thymeleafDemo.Resposity.DeviceRepo;
import lombok.RequiredArgsConstructor;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.client.RestTemplate;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

@Controller
@RequiredArgsConstructor
public class WebSensorController {

    private final DeviceRepo repo;


    @RequestMapping("/Dbsensor/StartHere")
    public String StartHere() {
        return "start.html";
    }

    // välj mellan senaste och historiska mätningar
    @PostMapping("/Dbsensor/showDevice")
    public String pageTwo() {
        return "optionpage.html";
    }

    @GetMapping("Dbsensor/history")
    public String history(
            @RequestParam(value = "date", required = false)
            @DateTimeFormat(iso = DateTimeFormat.ISO.DATE) LocalDate date,
            Model model) {

        // plocka ut alla sensorer från alla devices
        List<Sensor> allSensors = repo.findAll().stream()
                .flatMap(device -> device.getSensors().stream())
                .collect(Collectors.toList());

        List<Sensor> filtered;

        if (date != null) {
            filtered = allSensors.stream()
                    .filter(s -> s.getCreationDate() != null
                            && s.getCreationDate().toLocalDate().equals(date))
                    .toList();
            model.addAttribute("chosenDate", date);
        } else {
            filtered = allSensors;
        }

        int totalCount = filtered.size();

        model.addAttribute("totalReadings", totalCount);
        model.addAttribute("sensors", filtered);
        return "history";
    }


    @GetMapping("/Dbsensor/latest")
    public String SensorDataCollection(Model model) {
        RestTemplate restTemplate = new RestTemplate();

        try {
            //get latest device reading
            Device latestDevice = restTemplate.getForObject("http://localhost:8080/Dbsensor/Senast", Device.class);
            model.addAttribute("latestDevice", latestDevice);

            //get all devices
            ResponseEntity<List<Device>> response = restTemplate.exchange(
                    "http://localhost:8080/Dbsensor",
                    HttpMethod.GET,
                    null,
                    new ParameterizedTypeReference<List<Device>>() {}
            );
            List<Device> allDevices = response.getBody();
            model.addAttribute("allDevices", allDevices);

            //Extract all sensor readings from all devices
            List<Sensor> allSensors = new ArrayList<>();
            if (allDevices != null) {
                for (Device device : allDevices) {
                    if (device.getSensors() != null) {
                        allSensors.addAll(device.getSensors());
                    }
                }
            }
            model.addAttribute("allSensors", allSensors);
            model.addAttribute("totalReadings", allSensors.size());

            //Get latest temp and humidity readings
            Sensor latestTemp = null;
            Sensor latestHumidity = null;
            Sensor latestLight = null;


            if(latestDevice != null && latestDevice.getSensors() != null) {
                for (Sensor sensor : latestDevice.getSensors()) {
                    if ("temperature".equalsIgnoreCase(sensor.getSensor_reading()) || ("temp".equalsIgnoreCase(sensor.getSensor_reading())) ){
                        latestTemp = sensor;
                    } else if ("light".equalsIgnoreCase(sensor.getSensor_reading())) {
                        latestLight = sensor;
                    } else if("humidity".equalsIgnoreCase(sensor.getSensor_reading())){
                        latestHumidity = sensor;
                    }
                }
            }

            model.addAttribute("latestTemp", latestTemp);
            model.addAttribute("latestLight", latestLight);
            model.addAttribute("latestHumidity", latestHumidity);


        } catch (Exception e) {
            System.out.println("No sensor data available: " + e.getMessage());
            model.addAttribute("latestDevice", null);
            model.addAttribute("allDevices", null);
            model.addAttribute("allSensors", null);
            model.addAttribute("totalReadings", 0);
            model.addAttribute("latestTemp", null);
            model.addAttribute("latestLight", null);
        }
        return "SensorDataCollection";
    }

}
