#include "header/coin.hpp"

Coin::Coin(int index, Platform& platform)/* : platform(platform)*/ {
    width = coinWidth;
    height = coinHeight;
    isAvailable = true;
    
    // if (Coin(index).getHasCoin()) {
    //     x = Coin(index).getCoinX();
    //     y = Coin(index).getCoinY();
    // } 
    // else
    if (platform.getHasCoin() == false) {
        x = platform.getX() + platform.getWidth() + 10;
        if (x + width > screenWidth) {
            x = platform.getX() - width - 10;
        }
        y = platform.getY() - height - 5;
    }

    // moveType = rand() % 2;

    // int coinInt = rand() % 4;
    
    // if (coinInt == 0 || index == 0)
    //     hasCoin = false;
    // else
    //     hasCoin = true;
    
    // coinX = x + width/2 - 24/2;
    // coinY = y - 24 - 5;
}

int Coin::getX() {
    return x;
}

int Coin::getY() {
    return y;
}

int Coin::getWidth() {
    return width;
}

int Coin::getHeight() {
    return height;
}

void Coin::setIsAvailable(bool value) {
    isAvailable = value;
}

bool Coin::getIsAvailable() {
    return isAvailable;
}

void Coin::updatePosition() {
    y += coinSpeed;

    // if (isMoving != 0) {
    //     if (isMoving == 1) {
    //         x-=CoinSpeed;
    //         if (x < 0) {
    //             x = 0;
    //             isMoving = 2;
    //         }
    //     } else if (isMoving == 2) {
    //         x+=CoinSpeed;
    //         if (x + width > screenWidth) {
    //             x = screenWidth - width;
    //             isMoving = 1;
    //         }
    //     } else {
    //         bool isLeft = rand() % 2;
    //         if (isLeft) {
    //             x-=CoinSpeed;
    //             isLeft = false;
    //         } else {
    //             x+=CoinSpeed;
    //             isLeft = true;
    //         }
    //     }
    // }

    if (y > screenHeight) {
        x = rand() % 660 + 20;
        y = 0 - height;
        isAvailable = true;
        // int coinInt = rand() % 4;
        
        // if (coinInt == 0)
        //     hasCoin = false;
        // else
        //     hasCoin = true;
    }
 
    // coinX = x + width/2 - 24/2;
    // coinY = y - 24 - 5;    
}


