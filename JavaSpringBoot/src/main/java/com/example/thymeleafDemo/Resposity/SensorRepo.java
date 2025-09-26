package com.example.thymeleafDemo.Resposity;

import com.example.thymeleafDemo.Model.Sensor;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.time.LocalDateTime;
import java.util.List;

public interface SensorRepo extends JpaRepository<Sensor, Long> {
    List<Sensor> findAllByCreationDateBetween(LocalDateTime start, LocalDateTime end);

}
