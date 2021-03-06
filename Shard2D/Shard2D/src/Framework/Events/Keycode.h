/*
The MIT License (MIT)

Copyright (c) 2021-2022 Filippo Alberto Munaro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

namespace Shard2D
{
    namespace Keycode
    {
        typedef enum
        {
            Unknown = 0,

            Return = '\r',
            Escape = '\x1B',
            Backspace = '\b',
            Tab = '\t',
            Space = ' ',
            Exclaim = '!',
            QuotedBL = '"',
            Hash = '#',
            Percent = '%',
            Dollar = '$',
            Ampersand = '&',
            Quote = '\'',
            LeftParen = '(',
            RightParen = ')',
            Asterisk = '*',
            Plus = '+',
            Comma = ',',
            Minus = '-',
            Period = '.',
            Slash = '/',
            No_0 = '0',
            No_1 = '1',
            No_2 = '2',
            No_3 = '3',
            No_4 = '4',
            No_5 = '5',
            No_6 = '6',
            No_7 = '7',
            No_8 = '8',
            No_9 = '9',
            Colon = ':',
            SemiColon = ';',
            Less = '<',
            Equals = '=',
            Greater = '>',
            Question = '?',
            At = '@',

            /*
               Skip uppercase letters
            */

            LeftBracket = '[',
            Backslash = '\\',
            RightBracket = ']',
            Caret = '^',
            Underscore = '_',
            BackQuote = '`',
            A = 'a',
            B = 'b',
            C = 'c',
            D = 'd',
            E = 'e',
            F = 'f',
            G = 'g',
            H = 'h',
            I = 'i',
            J = 'j',
            K = 'k',
            L = 'l',
            M = 'm',
            N = 'n',
            O = 'o',
            P = 'p',
            Q = 'q',
            R = 'r',
            S = 's',
            T = 't',
            U = 'u',
            V = 'v',
            W = 'w',
            X = 'x',
            Y = 'y',
            Z = 'z',

            CapsLock = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

            F1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
            F2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
            F3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
            F4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
            F5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
            F6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
            F7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
            F8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
            F9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
            F10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
            F11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
            F12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

            PrintScreen = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
            ScrollLock = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
            Pause = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
            Insert = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
            Home = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
            PageUp = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
            Delete = '\x7F',
            End = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
            PageDown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
            Right = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
            Left = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
            Down = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
            Up = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

            NumLockClear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
            NumLock_Divide = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
            NumLock_Multiply = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
            NumLock_Minus = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
            NumLock_Plus = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
            NumLock_Enter = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
            NumLock_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
            NumLock_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
            NumLock_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
            NumLock_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
            NumLock_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
            NumLock_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
            NumLock_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
            NumLock_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
            NumLock_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
            NumLock_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
            NumLock_Period = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

            Application = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
            Power = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
            NumLock_Equals = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
            F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
            F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
            F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
            F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
            F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
            F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
            F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
            F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
            F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
            F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
            F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
            F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
            Execute = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
            Help = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
            Menu = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
            Select = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
            Stop = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
            Again = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
            Undo = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
            Cut = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
            Copy = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
            Paste = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
            Find = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
            Mute = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
            VolumeUp = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
            VolumeDown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
            NumLock_Comma = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
            NumLock_EqualsAs400 =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

            SDLK_ALTERASE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
            SDLK_SYSREQ = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
            SDLK_CANCEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
            SDLK_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
            SDLK_PRIOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
            SDLK_RETURN2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
            SDLK_SEPARATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
            SDLK_OUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
            SDLK_OPER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
            SDLK_CLEARAGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
            SDLK_CRSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
            SDLK_EXSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

            SDLK_KP_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
            SDLK_KP_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
            SDLK_THOUSANDSSEPARATOR =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
            SDLK_DECIMALSEPARATOR =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
            SDLK_CURRENCYUNIT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
            SDLK_CURRENCYSUBUNIT =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
            SDLK_KP_LEFTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
            SDLK_KP_RIGHTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
            SDLK_KP_LEFTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
            SDLK_KP_RIGHTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
            SDLK_KP_TAB = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
            SDLK_KP_BACKSPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
            SDLK_KP_A = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
            SDLK_KP_B = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
            SDLK_KP_C = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
            SDLK_KP_D = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
            SDLK_KP_E = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
            SDLK_KP_F = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
            SDLK_KP_XOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
            SDLK_KP_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
            SDLK_KP_PERCENT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
            SDLK_KP_LESS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
            SDLK_KP_GREATER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
            SDLK_KP_AMPERSAND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
            SDLK_KP_DBLAMPERSAND =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
            SDLK_KP_VERTICALBAR =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
            SDLK_KP_DBLVERTICALBAR =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
            SDLK_KP_COLON = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
            SDLK_KP_HASH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
            SDLK_KP_SPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
            SDLK_KP_AT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
            SDLK_KP_EXCLAM = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
            SDLK_KP_MEMSTORE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
            SDLK_KP_MEMRECALL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
            SDLK_KP_MEMCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
            SDLK_KP_MEMADD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
            SDLK_KP_MEMSUBTRACT =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
            SDLK_KP_MEMMULTIPLY =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
            SDLK_KP_MEMDIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
            SDLK_KP_PLUSMINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
            SDLK_KP_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
            SDLK_KP_CLEARENTRY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
            SDLK_KP_BINARY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
            SDLK_KP_OCTAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
            SDLK_KP_DECIMAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
            SDLK_KP_HEXADECIMAL =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

            SDLK_LCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
            SDLK_LSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
            SDLK_LALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
            SDLK_LGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
            SDLK_RCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
            SDLK_RSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
            SDLK_RALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
            SDLK_RGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

            SDLK_MODE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

            SDLK_AUDIONEXT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
            SDLK_AUDIOPREV = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
            SDLK_AUDIOSTOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
            SDLK_AUDIOPLAY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
            SDLK_AUDIOMUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
            SDLK_MEDIASELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
            SDLK_WWW = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
            SDLK_MAIL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
            SDLK_CALCULATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
            SDLK_COMPUTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
            SDLK_AC_SEARCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
            SDLK_AC_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
            SDLK_AC_BACK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
            SDLK_AC_FORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
            SDLK_AC_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
            SDLK_AC_REFRESH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
            SDLK_AC_BOOKMARKS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

            SDLK_BRIGHTNESSDOWN =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
            SDLK_BRIGHTNESSUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
            SDLK_DISPLAYSWITCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
            SDLK_KBDILLUMTOGGLE =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
            SDLK_KBDILLUMDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
            SDLK_KBDILLUMUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
            SDLK_EJECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
            SDLK_SLEEP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP),
            SDLK_APP1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP1),
            SDLK_APP2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP2),

            SDLK_AUDIOREWIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOREWIND),
            SDLK_AUDIOFASTFORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOFASTFORWARD)
        } Key;
    }
}
