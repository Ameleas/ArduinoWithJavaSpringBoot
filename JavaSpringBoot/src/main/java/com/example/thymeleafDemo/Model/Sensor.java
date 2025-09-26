package com.example.thymeleafDemo.Model;


import com.fasterxml.jackson.annotation.JsonBackReference;
import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.hibernate.annotations.CreationTimestamp;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Data
@Entity
@Table(name="sensor_reading")

@NoArgsConstructor
@AllArgsConstructor


public class Sensor {
    @Id
    @GeneratedValue
    protected Long id;
    protected String sensor_reading;
    protected float value;


    public Sensor(String sensor_reading, float value) {
        this.sensor_reading = sensor_reading;
        this.value = value;
    }
    @ManyToOne
    @JoinColumn(name = "device_id", nullable = false)
    @JsonBackReference
    private Device device;


  @CreationTimestamp
    private LocalDateTime creationDate;




}
