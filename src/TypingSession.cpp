#include "FaceEngine/TypingSession.h"
#include "FaceEngine/Inputs.h"

#define FACE_ASCII_ALPHABET_START 65
#define FACE_ASCII_ALPHABET_END 90

namespace FaceEngine
{
    TypingSession::TypingSession()
    {
        _text = "";
        _insertPosition = 0;
    }

    TypingSession::~TypingSession()
    {

    }

    void TypingSession::Update(FaceEngine::GameUpdate* gameUpdate)
    {
        std::vector<FaceEngine::TypedKey> keysTyped = gameUpdate->GetKeysTyped();

        for (int i = 0; i < keysTyped.size(); ++i)
        {
            switch (keysTyped[i].Key)
            {
                case FACE_KEY_BACKSPACE:
                    Backspace(keysTyped[i].Control);
                    return;

                case FACE_KEY_DELETE:
                    Delete(keysTyped[i].Control);
                    return;

                case FACE_KEY_ARROW_LEFT:
                    ShiftLeft(keysTyped[i].Control);
                    return;
                
                case FACE_KEY_ARROW_RIGHT:
                    ShiftRight(keysTyped[i].Control);
                    return;
            }

            AddChar(GetChar(keysTyped[i]));
        }
    }

    void TypingSession::AddChar(char character)
    {
        if (character == 0)
        {
            return;
        }

        _text.insert(_insertPosition, 1, character);
        _insertPosition++;
    }

    char TypingSession::GetChar(FaceEngine::TypedKey typedKey)
    {
        if (typedKey.Key >= FACE_ASCII_ALPHABET_START && typedKey.Key <=FACE_ASCII_ALPHABET_END)
        {
            return typedKey.Shift ? typedKey.Key: typedKey.Key + 32;
        }

        switch (typedKey.Key)
        {
            case FACE_KEY_SPACEBAR:
                return ' ';
            case FACE_KEY_APOSTROPHE:
                return typedKey.Shift ? '\"' : '\'';
            case FACE_KEY_COMMA:
                return typedKey.Shift ? '<' : ',';
            case FACE_KEY_MINUS:
                return typedKey.Shift ? '_' : '-';
            case FACE_KEY_PERIOD:
                return typedKey.Shift ? '>' : '.';
            case FACE_KEY_SLASH:
                return typedKey.Shift ? '?' : '/';
            case FACE_KEY_NUM1:
                return typedKey.Shift ? '!' : '1';
            case FACE_KEY_NUM2:
                return typedKey.Shift ? '@' : '2';
            case FACE_KEY_NUM3:
                return typedKey.Shift ? '#' : '3';
            case FACE_KEY_NUM4:
                return typedKey.Shift ? '$' : '4';
            case FACE_KEY_NUM5:
                return typedKey.Shift ? '%' : '5';
            case FACE_KEY_NUM6:
                return typedKey.Shift ? '^' : '6';
            case FACE_KEY_NUM7:
                return typedKey.Shift ? '&' : '7';
            case FACE_KEY_NUM8:
                return typedKey.Shift ? '*' : '8';
            case FACE_KEY_NUM9:
                return typedKey.Shift ? '(' : '9';   
            case FACE_KEY_NUM0:
                return typedKey.Shift ? ')' : '0';
            case FACE_KEY_SEMICOLON:
                return typedKey.Shift ? ':' : ';';
            case FACE_KEY_EQUALS:
                return typedKey.Shift ? '+' : '=';
            case FACE_KEY_BRACKET_LEFT:
                return typedKey.Shift ? '{' : '[';
            case FACE_KEY_BACKSLASH:
                return typedKey.Shift ? '|' : '\\';
            case FACE_KEY_BRACKET_RIGHT:
                return typedKey.Shift ? '}' : ']';
            case FACE_KEY_BACKTICK:
                return typedKey.Shift ? '~' : '`';
            case FACE_KEY_TAB:
                return 9; // vs code doesn't support tab characters.
            default:
                return 0;
        }
    }

    void TypingSession::Backspace(const bool ctrl)
    {
        if (_insertPosition == 0)
        {
            return;
        }

        if (!ctrl)
        {
            _text.erase(_insertPosition - 1, 1);
            _insertPosition--;
        }
        // else 
        // {
        //     if (_text[_insertPosition - 1] == ' ')
        //     {
        //         _text.erase(_insertPosition - 1, _insertPosition);
        //         _insertPosition--;
        //     }

        //     for (int i = _insertPosition - 1; i > 0; ++i) // might be bug relating to changing insertposition
        //     {
        //         if (_text[i] != ' ')
        //         {
        //             _text.erase(_insertPosition - 1);
        //             _insertPosition--;
        //         }
        //     }
        // }
    }

    void TypingSession::Delete(const bool ctrl)
    {

    }

    void TypingSession::ShiftLeft(const bool ctrl)
    {
        if (_insertPosition == 0)
        {
            return;
        }

        if (!ctrl)
        {
            _insertPosition--;
        }
        // else
        // {
        //     if (_text[_insertPosition - 1] == ' ')
        //     {
        //         _insertPosition--;
        //     }

        //     for (int i = _insertPosition - 1; i > 0; ++i) // might be bug relating to changing insertposition
        //     {
        //         if (_text[i] != ' ' || _insertPosition == 0)
        //         {
        //             _insertPosition--;
        //         }
        //     }
        // }
    }

    void TypingSession::ShiftRight(const bool ctrl)
    {
        if (_insertPosition == _text.length())
        {
            return;
        }

        if (!ctrl)
        {
            _insertPosition++;
        }
        // else
        // {
        //     if (_text[_insertPosition - 1] == ' ')
        //     {
        //         _insertPosition--;
        //     }

        //     for (int i = _insertPosition - 1; i > 0; ++i) // might be bug relating to changing insertposition
        //     {
        //         if (_text[i] != ' ' || _insertPosition == 0)
        //         {
        //             _insertPosition--;
        //         }
        //     }
        // }
    }

    std::string TypingSession::GetText() const
    {
        return _text;
    }

    int TypingSession::GetInsertPosition() const
    {
        return _insertPosition;
    }

    void TypingSession::SetInsertPosition(int insertPosition)
    {
        if (insertPosition < 0 || insertPosition > _text.length())
        {
            return;
        }

        _insertPosition = insertPosition;
    }
}