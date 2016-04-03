# PingPong-Counter
An Arduino based Display to indicate Points of a Ping Pong match

The Display contains 4 large seven-segment-numbers. They are positioned in two groups: left and right.


FUNCTIONALITY:

- When a player scores a point he can click a button on his side of the Ping Pong table and his points on the display will increase by one.
- When a player mistankenly pressed the button he can afterwards correct his score by doubleclicking the button which will decrease his score by 1.
- whenever a button was pressed a short soundeffect will occure so no one can secretly increase his/her points.
- The decimalpoints on the display are used to indicated which of the player has "Anpiels".
- As there is no rule which player has "Anspiel" at the beginning of the game, one can change the indicater by doubleclicking either button while the score is still 0:0


Hardware List:
- Arduino UNO
- Screw Shield from https://www.sparkfun.com/products/9729
- Large Seven Segment Display from https://www.sparkfun.com/products/8530
- Digit Driver from https://www.sparkfun.com/products/8530
- Arcade Buttons from https://www.sparkfun.com/products/9337
- Piezzo Speaker from https://www.sparkfun.com/products/7950
