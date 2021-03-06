// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*
    Apple Macintosh original/512/Plus keyboard
    Emulation by R. Belmont

    Port definitions from "IM Underground Volume 1"
    http://bitsavers.org/pdf/apple/mac/IM_Underground_Vol_1_1985.pdf

    Key matrix for keyboard:

    Cols  0   1   2   3   4   5   6   7   8    Rows
          G   B   T   5   0   P   ;   .  n/a     0
          H  n/a  Y   6   8   I   K   M  Enter   1
          F   V   R   4   -   [   '   N  Backsp  2
          D   C   E   3   7   U   J   /   `      3
          S   X   W   2   9   O   L   ,  Space   4
          A   Z   Q   1   =   ]  Ret  \  Tab     5

    Port 0:

    x-------  Clock, pulled up, driven by the 8021
    -x------  Caps Lock
    --x-----  Row 5 readback (tied to Vcc for keypad)
    ---x----  Row 4 readback
    ----x---  Row 3 readback
    -----x--  Row 2 readback
    ------x-  Row 1 readback
    -------x  Row 0 readback

    Port 1:

    x-------  Column 8 strobe
    -x------  Column 7 strobe
    --x-----  Column 6 strobe
    ---x----  Column 5 strobe
    ----x---  Column 4 strobe
    -----x--  Column 3 strobe
    ------x-  Column 2 strobe
    -------x  Column 1 strobe

    Port 2:
    x---      Command/Apple
    -x--      Shift
    --x-      Column 0 strobe
    ---x      Data, pulled up, driven by both sides

    The T1 line is "Option".

    There is a later M0110 keyboard version which uses a GI PIC1657; we do not have a dump of that version.
*/


#include "emu.h"
#include "mackbd.h"
#include "cpu/mcs48/mcs48.h"

//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define MACKBD_CPU_TAG  "mackbd"

//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

DEFINE_DEVICE_TYPE(MACKBD, mackbd_device, "mackbd", "Macintosh Keyboard")

ROM_START( mackbd )
	ROM_REGION(0x800, MACKBD_CPU_TAG, 0)
	// original Mac keyboard and optional external keypad
	ROM_LOAD( "ip8021h_2173.bin", 0x000000, 0x000400, CRC(5fbd9a94) SHA1(32a3b58afb445a8675b12a4de3aec2fa00c99222) )
	// Mac Plus all-in-one keyboard (not yet supported)
	ROM_LOAD( "341-0332-a.bin", 0x000400, 0x000400, CRC(6554f5b6) SHA1(a80404a122d74721cda13b285c412057c2c78bd7) )
ROM_END


static INPUT_PORTS_START( mackbd )
	PORT_START("COL0")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_G) PORT_CHAR('g') PORT_CHAR('G')
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_H) PORT_CHAR('h') PORT_CHAR('H')
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_F) PORT_CHAR('f') PORT_CHAR('F')
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_D) PORT_CHAR('d') PORT_CHAR('D')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_S) PORT_CHAR('s') PORT_CHAR('S')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_A) PORT_CHAR('a') PORT_CHAR('A')

	PORT_START("COL1")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_B) PORT_CHAR('b') PORT_CHAR('B')
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_UNKNOWN)
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_V) PORT_CHAR('v') PORT_CHAR('V')
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_C) PORT_CHAR('c') PORT_CHAR('C')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_X) PORT_CHAR('x') PORT_CHAR('X')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Z) PORT_CHAR('z') PORT_CHAR('Z')

	PORT_START("COL2")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_T) PORT_CHAR('t') PORT_CHAR('T')
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Y) PORT_CHAR('y') PORT_CHAR('Y')
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_R) PORT_CHAR('r') PORT_CHAR('R')
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_E) PORT_CHAR('e') PORT_CHAR('E')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_W) PORT_CHAR('w') PORT_CHAR('W')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Q) PORT_CHAR('q') PORT_CHAR('Q')

	PORT_START("COL3")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_5) PORT_CHAR('5') PORT_CHAR('%')
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_6) PORT_CHAR('6') PORT_CHAR('^')
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_4) PORT_CHAR('4') PORT_CHAR('$')
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_3) PORT_CHAR('3') PORT_CHAR('#')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_2) PORT_CHAR('2') PORT_CHAR('@')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_1) PORT_CHAR('1') PORT_CHAR('!')

	PORT_START("COL4")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_0) PORT_CHAR('0') PORT_CHAR(')')
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_8) PORT_CHAR('8') PORT_CHAR('*')
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_MINUS)  PORT_CHAR('-') PORT_CHAR('_')
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_7) PORT_CHAR('7') PORT_CHAR('&')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_9) PORT_CHAR('9') PORT_CHAR('(')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_EQUALS) PORT_CHAR('=') PORT_CHAR('+')

	PORT_START("COL5")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_P) PORT_CHAR('p') PORT_CHAR('P')
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_I) PORT_CHAR('i') PORT_CHAR('I')
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_OPENBRACE)  PORT_CHAR('[') PORT_CHAR('{')
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_U) PORT_CHAR('u') PORT_CHAR('U')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_O) PORT_CHAR('o') PORT_CHAR('O')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_CLOSEBRACE) PORT_CHAR(']') PORT_CHAR('}')

	PORT_START("COL6")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_COLON)  PORT_CHAR(';') PORT_CHAR(':')
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_K) PORT_CHAR('k') PORT_CHAR('K')
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_QUOTE)  PORT_CHAR('\'') PORT_CHAR('"')
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_J) PORT_CHAR('j') PORT_CHAR('J')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_L) PORT_CHAR('l') PORT_CHAR('L')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_ENTER) PORT_CHAR('\r') PORT_NAME("Return")

	PORT_START("COL7")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_STOP) PORT_CHAR('.') PORT_CHAR('>')
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_M) PORT_CHAR('m') PORT_CHAR('M')
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_N) PORT_CHAR('n') PORT_CHAR('N')
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_SLASH) PORT_CHAR('/') PORT_CHAR('?')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_COMMA) PORT_CHAR(',') PORT_CHAR('<')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_BACKSLASH) PORT_CHAR('\\') PORT_CHAR('|')

	PORT_START("COL8")
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_UNKNOWN)
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_UNKNOWN)
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_BACKSPACE)  PORT_CHAR(8)
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_TILDE) PORT_CHAR('`') PORT_CHAR('~')
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_SPACE) PORT_CHAR(' ')
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_TAB) PORT_CHAR('\t')

	PORT_START("MODS")
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Caps Lock") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Option") PORT_CODE(KEYCODE_LALT) PORT_CHAR(UCHAR_SHIFT_2)
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Shift") PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT) PORT_CHAR(UCHAR_SHIFT_1)
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Command") PORT_CODE(KEYCODE_LCONTROL)
INPUT_PORTS_END

//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

void mackbd_device::device_add_mconfig(machine_config &config)
{
	mcs48_cpu_device &cpu(I8021(config, m_maincpu, 3000000));   // "the approximate clock rate of the MPU is 3 MHz"
	cpu.bus_in_cb().set(FUNC(mackbd_device::p0_r));
	cpu.bus_out_cb().set(FUNC(mackbd_device::p0_w));
	cpu.p1_in_cb().set(FUNC(mackbd_device::p1_r));
	cpu.p1_out_cb().set(FUNC(mackbd_device::p1_w));
	cpu.p2_in_cb().set(FUNC(mackbd_device::p2_r));
	cpu.p2_out_cb().set(FUNC(mackbd_device::p2_w));
	cpu.t1_in_cb().set_ioport("MODS").bit(1); // option
}

const tiny_rom_entry *mackbd_device::device_rom_region() const
{
	return ROM_NAME( mackbd );
}

ioport_constructor mackbd_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( mackbd );
}

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  mackbd_device - constructor
//-------------------------------------------------

mackbd_device::mackbd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, MACKBD, tag, owner, clock),
	m_maincpu(*this, MACKBD_CPU_TAG),
	m_col(*this, "COL%u", 0U),
	m_clkout_handler(*this),
	m_dataout_handler(*this)
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void mackbd_device::device_start()
{
	m_clkout_handler.resolve_safe();
	m_dataout_handler.resolve_safe();
	m_sync = timer_alloc(0);
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void mackbd_device::device_reset()
{
	p0 = p1 = p2 = 0xff;
	datain = true;
	m_clkout_handler(1);
	m_dataout_handler(1);
}

u8 mackbd_device::p0_r()
{
	u8 ret = p0;

	for(int i=0; i<8; i++)
		if(!(p1 & (1<<i)))
			ret &= m_col[i+1]->read();

	if(!(p2 & 0x02))
		ret &= m_col[0]->read();

	// capslock
	if(!ioport("MODS")->read() & 0x1)
		ret &= ~0x40;

	return ret;
}

void mackbd_device::p0_w(u8 data)
{
	u8 delta = p0 ^ data;
	p0 = data;

	if(delta & 0x80)
		m_sync->adjust(attotime::zero);
}

void mackbd_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	m_clkout_handler(p0 & 0x80 ? ASSERT_LINE : CLEAR_LINE);
}

u8 mackbd_device::p1_r()
{
	return p1;
}

void mackbd_device::p1_w(u8 data)
{
	p1 = data;
}

u8 mackbd_device::p2_r()
{
	// Keypad has bit 5 connected to GND, but this is the keyboard.
	u8 ret = p2;
	if(!datain)
		ret &= 0xfe;
	ret &= ioport("MODS")->read() | ~0x0c;
	return ret;
}

void mackbd_device::p2_w(u8 data)
{
	p2 = data;
	m_dataout_handler(p2 & datain & 1);
}

void mackbd_device::datain_w(int state)
{
	datain = state;
}
