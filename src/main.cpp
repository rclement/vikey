#include <VirtualKeyboard.h>
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    vikey::VirtualKeyboard vk(0);

    if (!vk.connect()) {
        return -1;
    }

    bool stop = false;
    std::string cmd;

    while (!stop) {
        std::cin >> cmd;

        if (cmd == "q" || cmd == "stop" || cmd == "exit") {
            stop = true;
        } else {
            vk.noteOn(64, 101);
            vk.noteOff(64);
            vk.controlChange(0, 67);
            vk.programChange(88);
            vk.pitchBendChange(200);
            vk.polyphonicKeyPressure(67, 108);
            vk.channelPressure(109);
        }
    }

    (void) vk.disconnect();

    return 0;
}

