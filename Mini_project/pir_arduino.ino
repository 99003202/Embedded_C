#include<SPI.h>
volatile boolean rx_d;
volatile uint16_t slave_rxd;
void setup()
{
  Serial.begin(9600);
  pinMode(MISO,OUTPUT);                  
  pinMode(10,INPUT);
  digitalWrite(10,LOW);
  SPCR |= _BV(SPE);                      
  received_data = false;
  SPI.attachInterrupt();
  Serial.print("SYSTEM BOOTING>...........");
  delay(2000);
  Serial.print("SYSTEM READY");  
}

ISR(SPI_STC_vect)
{
  slave_rxd = SPDR;
  rx_d = true;
}
void loop()
{
  if (rx_d)
  {
    if (slave_rxd!=0)
    {
      rx_d=false;
      Serial.println("Motion Detected");
      delay(200);
    }
    else
    {   
            rx_d=false;
            Serial.println("No Motion");
            delay(200);

    }
  }
}
