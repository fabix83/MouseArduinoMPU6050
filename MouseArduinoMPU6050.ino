/*

	Autor: Fábio Felix
	https://github.com/fabix83/MouseArduinoMPU6050

	Mouse Virtual construido com a comunicação de Arduino Pro Micro 
	e MPU6050

	Necessário uso das seguintes bibliotecas: MPU6050 e I2Cdev

	Código de Apoio: 
	Arduino Meets Linux:
	The User's Guide to Arduino Yún Development
	Copyright (c) 2015, Bob Hammell.
	Disponível em: http://arduinomeetslinux.com/content.php?p=5
	
*/

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

//Constante do Endereço do MPU
MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

void setup() {
	//Inicializa a biblioteca I2C e conecta dispositivos
	Wire.begin();
	//Inicializa o sensor
	mpu.initialize();
	if (!mpu.testConnection()) {
		while (1);
  	}
}

void loop() {
	//captura dados do sensor
	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

	//mapeia os dados dentro de um intervalo mais aceitável. a divisão serve para estabilizar o mouse.
	int vx = map(gx, -16000, 16000, 90, -90)/1.25; //movimento vertical do mouse.
	int vy = map(gy, -16000, 16000, 90, -90)/1.25; //movimento horizontal

	//move o mouse através das coordenadas remapeadas
	Mouse.move(vy, -vx);

	//espera em ms. Serve para delimitar a velocidade do mouse
	delay(9);
}
