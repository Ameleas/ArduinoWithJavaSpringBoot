package com.example.thymeleafDemo.Resposity;

import com.example.thymeleafDemo.Model.Device;
import org.springframework.data.jpa.repository.JpaRepository;

public interface DeviceRepo extends JpaRepository<Device,Long> {
}
