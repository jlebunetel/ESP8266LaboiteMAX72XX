# ESP8266LaboiteMAX72XX
Arduino library for ESP8266 to interface with MAX7219 and MAX7221

# Connections

<table>
  <tr>
    <th colspan=2>NodeMCU</th><th>LED Matrix</th>
  </tr>
  <tr>
    <th>Pin</th><th>GPIO</th><th>Pin</th>
  </tr>
  <tr>
    <td>Vin (+5V)</td><td>-</td><td>+12V</td>
  </tr>
  <tr>
    <td>GND</td><td>-</td><td>GND</td>
  </tr>
  <tr>
    <td>D7</td><td>GPIO13</td><td>DIN</td>
  </tr>
  <tr>
    <td>D8</td><td>GPIO15</td><td>CS</td>
  </tr>
  <tr>
    <td>D5</td><td>GPIO14</td><td>CLK</td>
  </tr>
</table>

![Shéma électronique](https://raw.githubusercontent.com/laboiteproject/laboite-maker/master/images/laboite_bb_1.png)
