/*
*** Copyright 2021 ProximaX Limited. All rights reserved.
*** Use of this source code is governed by the Apache 2.0
*** license that can be found in the LICENSE file.
*/
#pragma once

#include "libtorrent/sha1_hash.hpp"
#include <libtorrent/kademlia/ed25519.hpp>

namespace libtorrent {

struct RawBuffer
{
    constexpr RawBuffer( uint8_t* data, size_t size ) : m_data(data), m_size(size) {}

    uint8_t* m_data;
    size_t   m_size;
};

class session_delegate {
    public:
        virtual ~session_delegate() = default;

        // It will be called on 'replicator' side,
        // when 'downloader' requests piece
        virtual bool checkDownloadLimit( std::vector<uint8_t> reciept,
                                         sha256_hash downloadChannelId,
                                         size_t downloadedSize )
        {
            return true;
        }

        // It will be called on 'download' side
        // when a piece is received
        virtual void onPiece( size_t pieceSize )
        {
        }

        virtual void sign( const uint8_t* bytes, size_t size, std::array<uint8_t,64>& signature ) = 0;

        virtual bool verify( const std::array<uint8_t,32>& publicKey,
                            const uint8_t* bytes, size_t size,
                             const std::array<uint8_t,64>& signature ) = 0;

        virtual const std::array<uint8_t,32>& publicKey() = 0;


        virtual const char* dbgOurPeerName() = 0;
    };

};
