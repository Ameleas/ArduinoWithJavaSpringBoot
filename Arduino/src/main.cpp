#include <util/delay.h>
#include "sensor.h"


int main(void)
{
    
  initAdc();
  initUsart();

    while (1) 
    {
    readTmp36();
    readLDR();
    printSensorValue();
  
    /* Wait for 10s */
		_delay_ms(10000);
	
    }
    
}





  // Placeholder function for future sensor analysis