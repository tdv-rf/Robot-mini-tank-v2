#include <Arduino.h>
#include "MatrixDisplay.h"

uint8_t SCL_Pin; //Set clock pin to A5
uint8_t SDA_Pin; //Set data pin to A4

MatrixDisplay::~MatrixDisplay()
{
}

MatrixDisplay::MatrixDisplay()
{
}

/******************Function for dot matrix***************/

void MatrixDisplay::init(uint8_t scl_pin, uint8_t sda_pin)
{
  SCL_Pin = scl_pin;
  SDA_Pin = sda_pin;
  pinMode(SCL_Pin, OUTPUT);
  pinMode(SDA_Pin, OUTPUT);
  matrix_display(clear);   //Clear the display
  matrix_display(start01); //show start pattern
}

//The condition starting to transmit data
void MatrixDisplay::IIC_start()
{
  digitalWrite(SCL_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, LOW);
  delayMicroseconds(3);
}
//convey data
void MatrixDisplay::IIC_send(unsigned char send_data)
{
  for (char i = 0; i < 8; i++) //Each byte has 8 bits 8bits for every character
  {
    digitalWrite(SCL_Pin, LOW); //pull down clock pin SCL Pin to change the signals of SDA
    delayMicroseconds(3);
    if (send_data & 0x01) //set high and low level of SDA_Pin according to 1 or 0 of every bit
    {
      digitalWrite(SDA_Pin, HIGH);
    }
    else
    {
      digitalWrite(SDA_Pin, LOW);
    }
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, HIGH); //pull up clock pin SCL_Pin to stop transmitting data
    delayMicroseconds(3);
    send_data = send_data >> 1; // detect bit by bit, so move the data right by one
  }
}
//The sign that data transmission ends
void MatrixDisplay::IIC_end()
{
  digitalWrite(SCL_Pin, LOW);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, HIGH);
  delayMicroseconds(3);
}

// this function is used for dot matrix display
void MatrixDisplay::matrix_display(unsigned char matrix_value[])
{
  Serial.println("matrix_display");
  IIC_start();
  IIC_send(0xc0);              //Choose address
  for (int i = 0; i < 16; i++) //pattern data has 16 bits
  {
    IIC_send(matrix_value[i]); //data to convey patterns
  }
  IIC_end(); //end to convey data pattern

  IIC_start();
  IIC_send(0x8A); //display control, set pulse width to 4/16
  IIC_end();
}
