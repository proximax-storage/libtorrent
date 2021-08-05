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

        // Replicator behavior differs from client
        virtual bool isClient() const = 0;

        virtual void onHandshake( uint64_t uploadedSize )
        {
        }

        virtual uint8_t getUploadedSize( const std::array<uint8_t,32>& downloadChannelId )
        {
            // Now client does not calculate uploaded size (but not replivcator)
            return 0;
        }

        // It will be called on 'replicator' side,
        // when 'downloader' requests piece
        virtual bool checkDownloadLimit( const std::array<uint8_t,64>& signature,
                                         const std::array<uint8_t,32>& downloadChannelId,
                                        uint64_t downloadedSize )
        {
            // 'client' always returns 'true'
            return true;
        }

        // It will be called,
        // when a piece is received,
        // for accumulating downloaded data size
        virtual void onPieceReceived( uint64_t pieceSize )
        {
            // now 'replicator' does nothing in this case
        }

        // It will be called,
        // when a piece is sent,
        // for accumulating sent data size
        virtual void onPieceSent( const std::array<uint8_t,32>& downloadChannelId, uint64_t pieceSize )
        {
            // now 'client' does nothing in this case
        }

        // It will be called to sign random sequence (for handshake)
        virtual void sign( const uint8_t* bytes, size_t size,
                           std::array<uint8_t,64>& outSignature ) = 0;

        // It will be called to verify handshake
        virtual bool verify( const uint8_t* bytes, size_t size,
                             const std::array<uint8_t,32>& publicKey,
                             const std::array<uint8_t,64>& signature ) = 0;

        // It will be called to sign receipt
        virtual void sign( const std::array<uint8_t,32>& replicatorPublicKey,
                          uint64_t&                      outDownloadedSize,
                          std::array<uint8_t,64>&        outSignature ) = 0;

        // It will be called to verify receipt
        virtual bool verify( const std::array<uint8_t,32>&  clientPublicKey,
                             uint64_t                       downloadedSize,
                             const std::array<uint8_t,64>&  signature ) = 0;

        virtual const std::array<uint8_t,32>& publicKey() = 0;

        // It will be called when 'client' connects to 'replicator' (handshake)
        virtual const std::optional<std::array<uint8_t,32>> downloadChannelId() = 0;

        // It will be called when 'replicator' answers to 'client' (extended handshake)
        virtual uint64_t downloadedSize( const std::array<uint8_t,32>& downloadChannelId ) = 0;

        // It will be called when 'client' receives an answer from 'replicator' (extended handshake)
        // 'downloadedSize' should be set to proper value (last 'downloadedSize' of peviuos peer_connection)
        virtual void setDownloadedSize( uint64_t downloadedSize ) = 0;

        // They will be called when 'client' requests a piece from 'replicator' (handshake)
        virtual uint64_t downloadedSize() = 0;
        virtual uint64_t requestedSize() = 0;


        virtual const char* dbgOurPeerName() = 0;
    };

    inline void toString( const uint8_t* in, int const len, char* out)
    {
        const char* hex_chars = "0123456789abcdef";

        int idx = 0;
        for (int i = 0; i < len; ++i)
        {
            out[idx++] = hex_chars[std::uint8_t(in[i]) >> 4];
            out[idx++] = hex_chars[std::uint8_t(in[i]) & 0xf];
        }
    }

    template <size_t N>
    inline std::string toString( std::array<uint8_t,N> in )
    {
        std::string ret;
        if ( in.size() > 0 )
        {
            ret.resize( std::size_t( 2*N ) );
            toString( in.data(), N, &ret[0]);
        }
        return ret;
    }

    inline std::string toHex( const char* ptr, size_t len )
    {
        std::string ret;
        if ( len > 0 )
        {
            ret.resize( size_t( 2*len ) );
            toString( reinterpret_cast<const uint8_t*>(ptr), len, &ret[0]);
        }
        return ret;
    }

};
