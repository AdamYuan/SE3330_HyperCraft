#ifndef HYPERCRAFT_COMMON_MESSAGE_HPP
#define HYPERCRAFT_COMMON_MESSAGE_HPP

#include <algorithm>
#include <cinttypes>
#include <string>
#include <string_view>
#include <vector>

namespace common {

enum class ClientMessages : uint8_t { kConnect, kDisconnect, kPing, kPosition, kRequestChunk, kChat, kCommand };
enum class ServerMessages : uint8_t { kValidate = 128, kDisconnect, kLoadChunk, kUpdateBlock, kPosition, kCommand };

} // namespace common

#endif
