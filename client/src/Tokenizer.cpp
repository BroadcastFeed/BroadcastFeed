#include "Tokenizer.h"

PacketType tokenizeStringToParamType(string message) {
    string token = message.substr(0, message.find(' '));
    std::transform(token.begin(),  token.end(),token.begin(), ::toupper);

    map<string, PacketType> commandToPacketMap = {
        {"FOLLOW", PacketType::FOLLOW},
        {"SEND", PacketType::SEND}
    };

    return commandToPacketMap.at(token);
}
