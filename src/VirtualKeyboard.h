#ifndef __VIKEY_VIRTUAL_KEYBOARD__
#define __VIKEY_VIRTUAL_KEYBOARD__

#include <RtMidi.h>

namespace vikey
{

/**
 * A virtual keyboard allows to simulate a MIDI keyboard sending messages on
 * a dedicated MIDI port by using a virtual output MIDI port.
 *
 * @ref http://www.midi.org/techspecs/midimessages.php
 */
class VirtualKeyboard
{
public:

    /**
     * Construct a virtual MIDI keyboard.
     *
     * @param[in] channel MIDI channel between 0 and 15 (default is 0)
     */
    explicit VirtualKeyboard(const unsigned char channel=0);

    /**
     * Destroy a virtual MIDI keyboard
     */
    virtual ~VirtualKeyboard();

    /**
     * Retrieve the current MIDI channel for the virtual keyboard.
     *
     * @return MIDI channel between 0 and 15
     */
    unsigned char channel() const;

    /**
     * Specify a new MIDI channel for the virtual keyboard.
     *
     * @param[in] channel MIDI channel between 0 and 15
     *
     * @return true if the channel could be set, false otherwise
     */
    bool setChannel(const unsigned char channel);

    /**
     * Connect the virtual MIDI keyboard by opening a virtual MIDI port.
     *
     * @param[in] portname Name of the MIDI port
     *
     * @return true if the virtual keyboard could be connected, false otherwise
     */
    bool connect(const std::string &portname="VirtualKeyboard");

    /**
     * Disconnect the virtual MIDI keyboard.
     *
     * @return true if the virtual keyboard could be disconnected, false otherwise
     */
    bool disconnect();

    /**
     * Send a note off message.
     *
     * This message is sent when a note is released (ended).
     *
     * @param[in] note The note number between 0 and 127
     *
     * @return true if the message could be sent, false otherwise
     */
    bool noteOff(const unsigned char note);

    /**
     * Send a note on message.
     *
     * This message is sent when a note is depressed (start).
     *
     * @param[in] note The note number between 0 and 127
     * @param[in] velocity The note velocity between 0 and 127
     *
     * @return true if the message could be sent, false otherwise
     */
    bool noteOn(const unsigned char note, const unsigned char velocity);

    /**
     * Send a control change message.
     *
     * This message is sent when a controller value changes.
     * Controllers include devices such as pedals and levers.
     * Controller numbers 120-127 are reserved as "Channel Mode Messages".
     *
     * @param[in] number The control number between 0 and 119
     * @param[in] value The control value between 0 and 127
     *
     * @return true if the message could be sent, false otherwise
     */
    bool controlChange(const unsigned char number, const unsigned char value);

    /**
     * Send a program change message.
     *
     * This message sent when the patch number changes.
     *
     * @param[in] number The program number between 0 and 127
     *
     * @return true if the message could be sent, false otherwise
     */
    bool programChange(const unsigned char number);

    /**
     * Send a pitch-bend change message.
     *
     * This message is sent to indicate a change in the pitch bender
     * (wheel or lever, typically).
     * The pitch bender is measured by a fourteen bit value.
     * Center (no pitch change) is 2000H.
     * Sensitivity is a function of the transmitter.
     *
     * @param[in] value The pitch-bend value between 0 and 32767 (middle is 8192)
     *
     * @return true if the message could be sent, false otherwise
     */
    bool pitchBendChange(const unsigned int value);

    /**
     * Send a polyphonic key pressure (after-touch) message.
     *
     * This message is most often sent by pressing down on the key after
     * it "bottoms out".
     *
     * @param[in] note The note number between 0 and 127
     * @param[in] pressure The note number between 0 and 127
     *
     * @return true if the message could be sent, false otherwise
     */
    bool polyphonicKeyPressure(const unsigned char note, const unsigned char pressure);

    /**
     * Send a channel pressure (after-touch) message.
     *
     * This message is most often sent by pressing down on the key after
     * it "bottoms out". This message is different from polyphonic after-touch.
     * Use this message to send the single greatest pressure value
     * (of all the current depressed keys).
     *
     * @param[in] pressure The note number between 0 and 127
     *
     * @return true if the message could be sent, false otherwise
     */
    bool channelPressure(const unsigned char pressure);

private:

    /**
     * Send a MIDI message.
     *
     * @param[in] message Pointer on the MIDI message to be sent
     *
     * @return true if the message could be sent, false otherwise
     */
    bool sendMidiMessage(std::vector<unsigned char> *message);

    unsigned char mChannel;
    RtMidiOut mMidiOut;
};

} /* namespace vikey */

#endif /* __VIRTUAL_KEYBOARD__ */

