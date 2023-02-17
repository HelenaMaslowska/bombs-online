# Bombs Online
Bombs online is 2D game made on Linux Ubuntu in C++ and using Qt Creator 6. Game can be played if you have <ins>**QT6 libraries**</ins> installed in your device.
Rules are simple:
1. Be the last one to stand!

Ok, there are some other rules...

## Rules
2. Use ```w, a, s, d``` to move and ```x``` to place bombs.
3. Kill other players.
4. Destroy crates to gain powerups.
5. Use powerups to increase your survivability.
6. Have fun!

### Powerups
- green - range 
- gray - max bombs 
- blue - speed 
- red - HP 
- yellow - immortality

## Getting started
You need to compile server on your computer, use this command. Use this folder [path](https://github.com/HelenaMaslowska/bombs-online/tree/main/Server)!
```c++
g++ server.cpp -o server -pthread
```
Execute server using this command: ```./server <port_number>```. Example is shown below.
```c++
./server 8080
```

After that, you can open clients/gamers using following command. Use this folder [path](https://github.com/HelenaMaslowska/bombs-online/tree/main/Game/build-skproject-Desktop_Qt_6_4_2_GCC_64bit-Release). You can have a lot of players playing in other rooms!
```c++
./skproject
```

## Screenshots with explanations
Please set these parameters before **start**!

* IP address, e.g. ```192.168.3.3``` or ```127.0.0.1``` which means localhost
* Port, e.g. ```8080```
* After that press ```Set up!```
* Input your beautiful ```Nickname``` and then press ```Start```

<p align="center">
<img src="https://user-images.githubusercontent.com/44245185/218344861-560514d0-8b37-4f42-99db-4147cd12f8f2.png">
<p>

Here is our game! When all gamers press ```Ready``` to start, game will start! 
<p align="center">
<img src="https://user-images.githubusercontent.com/44245185/218347507-2c9cd600-ec12-4976-85b1-a90c7131b9e2.png">
<p>


## License
Bombs Online is free and open source! All code in this repository is licensed under either:
* MIT License ([LICENSE-MIT](docs/LICENSE-MIT) or [http://opensource.org/licenses/MIT](http://opensource.org/licenses/MIT))
