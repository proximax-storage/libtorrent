/*
*** Copyright 2021 ProximaX Limited. All rights reserved.
*** Use of this source code is governed by the Apache 2.0
*** license that can be found in the LICENSE file.
*/
#pragma once

#include "libtorrent/sha1_hash.hpp"
#include <libtorrent/kademlia/ed25519.hpp>

#include <optional>

namespace libtorrent {

const uint32_t sf_is_replicator     = 0x01;
const uint32_t sf_is_receiver       = 0x02;
const uint32_t sf_has_modify_data   = 0x04;

class session_delegate {
    public:
        virtual ~session_delegate() = default;

        // Replicator behavior differs from client
        virtual bool isClient() const = 0;
    
        virtual void onTorrentDeleted( lt::torrent_handle ) = 0;
    
        virtual bool acceptConnection( const std::array<uint8_t,32>&  transactionHash,
                                       const std::array<uint8_t,32>&  peerPublicKey,
                                       bool*                          outIsDownloadUnlimited ) = 0;

        virtual void onDisconnected( const std::array<uint8_t,32>&  transactionHash,
                                     const std::array<uint8_t,32>&  peerPublicKey,
                                     int                            reason ) = 0;

        virtual void onHandshake( uint64_t uploadedSize )
        {
        }

        virtual uint8_t getUploadedSize( const std::array<uint8_t,32>& downloadChannelId )
        {
            // Now client does not calculate uploaded size (but not replivcator)
            return 0;
        }

        // It will be called on 'giving' side,
        // when 'downloader' requests piece
        virtual bool checkDownloadLimit( const std::array<uint8_t,64>&  signature,
                                         const std::array<uint8_t,32>&  downloadChannelId,
                                         uint64_t                       downloadedSize )
        {
            // 'client' always returns 'true'
            return true;
        }

        // will be called by libtorrent pugin when replicator receives receipt
        // (must be implemented by DefaultReplicator)
        virtual void sendReceiptToOtherReplicators( const std::array<uint8_t,32>&  downloadChannelId,
                                                    const std::array<uint8_t,32>&  clientPublicKey,
                                                    uint64_t                       downloadedSize,
                                                    const std::array<uint8_t,64>&  signature )
        {
            // 'client' ignores this call
        }

        // will be called by libtorrent pugin when new replicator or client endpoint is discovered
        // (must be implemented by DefaultReplicator)
        virtual void onEndpointDiscovered(const std::array<uint8_t, 32>& key,
                                          const std::optional<tcp::endpoint>& endpoint)
        {
            // 'client' ignores this call
        }

        // It will be called by client (or replicator-receiver),
        // when a piece is requested by receiver
        // (to accumulate requested data size; now it is not used)
        virtual void onPieceRequest( const std::array<uint8_t,32>&  transactionHash,
                                       const std::array<uint8_t,32>&  senderPublicKey,
                                       uint64_t                       pieceSize ) = 0;

        // It will be called by sender,
        // when a piece request received
        // (to accumulate requesting data size)
        virtual void onPieceRequestReceived( const std::array<uint8_t,32>&  transactionHash,
                                             const std::array<uint8_t,32>&  receiverPublicKey,
                                             uint64_t                       pieceSize ) = 0;

        // It will be called by sender,
        // when a piece is sent
        virtual void onPieceSent( const std::array<uint8_t,32>&  transactionHash,
                                  const std::array<uint8_t,32>&  receiverPublicKey,
                                  uint64_t                       pieceSize ) = 0;

        // It will be called,
        // when a piece is received,
        virtual void onPieceReceived( const std::array<uint8_t,32>&  transactionHash,
                                      const std::array<uint8_t,32>&  senderPublicKey,
                                      uint64_t                       pieceSize ) = 0;

        virtual void onAllOutgoingConnectionsClosed( const std::array<uint8_t,32>& /*transactionHash*/ )
        {
        }
    
        // It will be called to sign random sequence (for handshake)
        virtual void signHandshake( const uint8_t*              bytes,
                                    size_t                      size,
                                    std::array<uint8_t,64>&     outSignature ) = 0;

        // It will be called to verify handshake
        virtual bool verifyHandshake( const uint8_t*                 bytes,
                                      size_t                         size,
                                      const std::array<uint8_t,32>&  publicKey,
                                      const std::array<uint8_t,64>&  signature ) = 0;

//        // It will be called to sign random sequence (for handshake)
//        virtual void signMutableItem( const uint8_t*              bytes,
//                                    size_t                      size,
//                                    std::array<uint8_t,64>&     outSignature ) = 0;

        // It will be called to verify handshake
        virtual bool verifyMutableItem( const std::vector<char>& value,
                                        const int64_t& seq,
                                        const std::string& salt,
                                        const std::array<uint8_t,32>& pk,
                                        const std::array<uint8_t,64>& sig ) = 0;

        // It will be called to verify handshake
        virtual void signMutableItem( const std::vector<char>& value,
                                      const int64_t& seq,
                                      const std::string& salt,
                                      std::array<uint8_t,64>& sig ) = 0;

        // It will be called to sign receipt
        // (must be implemented by ClientSession)
        virtual void signReceipt( const std::array<uint8_t,32>& downloadChannelId,
                                  //                            clientPublicKey,        //it is accesible from ClientSession
                                  const std::array<uint8_t,32>& replicatorPublicKey,
                                  uint64_t                      downloadedSize,
                                  std::array<uint8_t,64>&       outSignature ) = 0;

        // It will be called to verify receipt and then accept it
        // (must be implemented by DownloadLimiter)
        virtual bool acceptReceipt( const std::array<uint8_t,32>&  downloadChannelId,
                                    const std::array<uint8_t,32>&  clientPublicKey,
                                    const std::array<uint8_t,32>&  replicatorPublicKey,
                                    uint64_t                       downloadedSize,
                                    const std::array<uint8_t,64>&  signature )
        {
            // now 'client' does nothing in this case
            return true;
        }

        // Replicator/Client public key
        virtual const std::array<uint8_t,32>& publicKey() = 0;

        // Endpoint associated with the key
        virtual std::optional<boost::asio::ip::tcp::endpoint> getEndpoint( const std::array<uint8_t,32>& key ) = 0;

        // It will be called when 'replicator' answers to 'client' (extended handshake)
        //virtual uint64_t receivedSize( const std::array<uint8_t,32>& downloadChannelId ) = 0;

        // It will be called when 'client' receives an answer from 'replicator' (extended handshake)
        // 'downloadedSize' should be set to proper value (last 'downloadedSize' of peviuos peer_connection)
        //virtual void setStartReceivedSize( uint64_t downloadedSize ) = 0;

        // They will be called when 'client' requests a piece from 'replicator' (handshake)
        virtual uint64_t receivedSize( const std::array<uint8_t,32>&  peerPublicKey ) = 0;
        virtual uint64_t requestedSize( const std::array<uint8_t,32>&  peerPublicKey )  = 0;

        virtual bool     isStopped()
        {
            return false;
        }

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

}
