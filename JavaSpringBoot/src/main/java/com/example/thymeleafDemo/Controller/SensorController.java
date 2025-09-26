package com.example.thymeleafDemo.Controller;


import com.example.thymeleafDemo.Resposity.SensorRepo;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller

public class SensorController {

    private SensorRepo sensorRepo;

    private SensorController(SensorRepo sensorRepo) {this.sensorRepo = sensorRepo;}

    @RequestMapping("/Dbsensor/StartHere")
    public String StartHere() {
        return "start.html";
    }

    // välj mellan senaste och historiska mätningar
    @PostMapping("/Dbsensor/showDevice")
    public String pageTwo() {
        return "optionpage.html";
    }

}


