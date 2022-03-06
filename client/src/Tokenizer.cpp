#include <stdexcept>
#include "Tokenizer.h"

//needs reference argument in order to remove command from message
PacketType tokenizeStringToParamType(string& message) {
    unsigned int tokenLength = message.find(' ');
    string token = message.substr(0, tokenLength);
    message.erase(0, tokenLength + 1);
    std::transform(token.begin(),  token.end(),token.begin(), ::toupper);
    map<string, PacketType> commandToPacketMap = {
        {"FOLLOW", PacketType::FOLLOW},
        {"SEND", PacketType::SEND}
    };

    return commandToPacketMap.at(token);
}
