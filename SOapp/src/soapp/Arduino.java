/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package soapp;

import com.fazecast.jSerialComm.SerialPort;

/**
 *
 * @author sharon
 */
public class Arduino {

    private SerialPort puerto;

    public boolean conectar() {
        String portName = "COM2";
        puerto = SerialPort.getCommPort(portName);
        puerto.openPort();
        puerto.setComPortParameters(9600, 8, 1, 0);
        puerto.setComPortTimeouts(puerto.TIMEOUT_WRITE_BLOCKING, 0, 0);
        return puerto.isOpen();
    }

    public void desconectar() {
        puerto.closePort();
        if (puerto != null && puerto.isOpen()) {
            puerto.closePort();
            System.out.println("Puerto cerrado con éxito");
        }
    }

    public void enviar(char c) {
        try {
            puerto.getOutputStream().write(c);
            puerto.getOutputStream().flush();
        } catch (Exception e) {
            System.out.println("Error" + e);
        } 
    }

}
