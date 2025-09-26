package com.example.thymeleafDemo.Controller;

import com.example.thymeleafDemo.Model.Sensor;
import com.example.thymeleafDemo.Resposity.DeviceRepo;
import lombok.RequiredArgsConstructor;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.time.LocalDate;
import java.util.List;
import java.util.stream.Collectors;

@Controller
@RequiredArgsConstructor
public class SensorWebController {

    private final DeviceRepo repo;

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
}
