#include <VirtualKeyboard.h>

namespace vikey
{

VirtualKeyboard::VirtualKeyboard(const unsigned char channel) :
    mChannel(0),
    mMidiOut()
{
    setChannel(channel);
}

VirtualKeyboard::~VirtualKeyboard()
{
    if (mMidiOut.isPortOpen()) {
        mMidiOut.closePort();
    }
}

unsigned char VirtualKeyboard::channel() const
{
    return mChannel;
}

bool VirtualKeyboard::setChannel(const unsigned char channel)
{
    if (channel > 0x0F) {
        mChannel = 0;
        return false;
    }

    mChannel = channel;

    return true;
}

bool VirtualKeyboard::connect(const std::string &portname)
{
    try {
        mMidiOut.openVirtualPort(portname);
    } catch (RtMidiError &error) {
        error.printMessage();
        return false;
    }

    return true;
}

bool VirtualKeyboard::disconnect()
{
    try {
        mMidiOut.closePort();
    } catch (RtMidiError &error) {
        error.printMessage();
        return false;
    }

    return true;
}

bool VirtualKeyboard::noteOff(const unsigned char note)
{
    if (note > 0x7F) {
        return false;
    }

    std::vector<unsigned char> message;
    message.push_back(0x80 + mChannel);
    message.push_back(note);
    message.push_back(0);

    return sendMidiMessage(&message);
}

bool VirtualKeyboard::noteOn(const unsigned char note, const unsigned char velocity)
{
    if (note > 0x7F || velocity > 0x7F) {
        return false;
    }

    std::vector<unsigned char> message;
    message.push_back(0x90 + mChannel);
    message.push_back(note);
    message.push_back(velocity);

    return sendMidiMessage(&message);
}

bool VirtualKeyboard::controlChange(const unsigned char number, const unsigned char value)
{
    if (number > 0x77 || value > 0x7F) {
        return false;
    }

    std::vector<unsigned char> message;
    message.push_back(0xB0 + mChannel);
    message.push_back(number);
    message.push_back(value);

    return sendMidiMessage(&message);
}

bool VirtualKeyboard::programChange(const unsigned char number)
{
    if (number > 0x7F) {
        return false;
    }

    std::vector<unsigned char> message;
    message.push_back(0xC0 + mChannel);
    message.push_back(number);

    return sendMidiMessage(&message);
}

bool VirtualKeyboard::pitchBendChange(const unsigned int value)
{
    if (value > 0x3FFF) {
        return false;
    }

    const unsigned char lsb = value & 0x007F;
    const unsigned char msb = value & 0x3F80;

    std::vector<unsigned char> message;
    message.push_back(0xE0 + mChannel);
    message.push_back(lsb);
    message.push_back(msb);

    return sendMidiMessage(&message);
}

bool VirtualKeyboard::polyphonicKeyPressure(const unsigned char note, const unsigned char pressure)
{
    if (note > 0x7F || pressure > 0x7F) {
        return false;
    }

    std::vector<unsigned char> message;
    message.push_back(0xA0 + mChannel);
    message.push_back(note);
    message.push_back(pressure);

    return sendMidiMessage(&message);
}

bool VirtualKeyboard::channelPressure(const unsigned char pressure)
{
    if (pressure > 0x7F) {
        return false;
    }

    std::vector<unsigned char> message;
    message.push_back(0xD0 + mChannel);
    message.push_back(pressure);

    return sendMidiMessage(&message);
}

bool VirtualKeyboard::sendMidiMessage(std::vector<unsigned char> *message)
{
    try {
        mMidiOut.sendMessage(message);
    } catch (RtMidiError &error) {
        error.printMessage();
        return false;
    }

    return true;
}

}; /* namespace vikey */

