/*
*** Copyright 2021 ProximaX Limited. All rights reserved.
*** Use of this source code is governed by the Apache 2.0
*** license that can be found in the LICENSE file.
*/
#pragma once

#include "libtorrent/sha1_hash.hpp"
#include <libtorrent/kademlia/ed25519.hpp>
#include <libtorrent/error_code.hpp>
#include <libtorrent/close_reason.hpp>

#include <optional>

namespace libtorrent {

namespace SiriusFlags {
    using type = uint8_t;
    enum : type {
        none                      = 0x00,
        peer_is_replicator        = 0x01,
        replicator_is_receiver    = 0x02,
        client_has_modify_data    = 0x04,
        client_is_receiver        = 0x08
    };
};

enum class connection_status {
    REJECTED, LIMITED, UNLIMITED
};

class session_delegate {
    public:
        virtual ~session_delegate() = default;

        // Replicator behavior differs from client
        virtual bool isClient() const = 0;
    
        virtual void onTorrentDeleted( lt::torrent_handle ) = 0;

        virtual void onCacheFlushed( lt::torrent_handle ) = 0;
    
        virtual connection_status acceptClientConnection( const std::array<uint8_t,32>&  channelId,
                                                          const std::array<uint8_t,32>&  peerKey,
                                                          const std::array<uint8_t,32>&  driveKey,
                                                          const std::array<uint8_t,32>&  fileHash,
                                                          lt::errors::error_code_enum&   outErrorCode )
        {
            outErrorCode = lt::errors::no_error;
            return connection_status::REJECTED;
        }

        virtual connection_status acceptReplicatorConnection( const std::array<uint8_t,32>&  driveKey,
                                                 const std::array<uint8_t,32>&  peerPublicKey )
        {
            //(???)
            // now client already accepts connection from any replicator ?
            return connection_status::REJECTED;
        }

        virtual void onDisconnected( const std::array<uint8_t,32>&  transactionHash,
                                     const std::array<uint8_t,32>&  peerPublicKey,
                                     int                            reason ) = 0;

        virtual void onHandshake( uint64_t uploadedSize )
        {
        }

//        virtual uint8_t getUploadedSize( const std::array<uint8_t,32>& downloadChannelId )
//        {
//            // Now client does not calculate uploaded size (but not replivcator)
//            return 0;
//        }

        // It will be called on 'giving' side,
        // when 'downloader' requests piece
        virtual bool checkDownloadLimit( const std::array<uint8_t,32>&  peerKey,
                                         const std::array<uint8_t,32>&  downloadChannelId,
                                         uint64_t                       downloadedSize,
                                         lt::errors::error_code_enum&   outErrorCode )
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
                                          const std::optional<udp::endpoint>& endpoint)
        {
        }

        // It will be called by client (or replicator-receiver),
        // when a piece is requested by receiver
        // (to accumulate requested data size; now it is not used)
        virtual void onPieceRequestWrite( const std::array<uint8_t,32>&  transactionHash,
                                          const std::array<uint8_t,32>&  senderPublicKey,
                                          uint64_t                       pieceSize ) = 0;

        // It will be called by sender,
        // when a piece request received
        // (to accumulate requesting data size)
        virtual bool onPieceRequestReceivedFromReplicator( const std::array<uint8_t,32>&  modifyTx,
                                                           const std::array<uint8_t,32>&  receiverPublicKey,
                                                           uint64_t                       pieceSize ) = 0;
    
        virtual bool onPieceRequestReceivedFromClient( const std::array<uint8_t,32>&      transactionHash,
                                                       const std::array<uint8_t,32>&      receiverPublicKey,
                                                       uint64_t                           pieceSize ) = 0;

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
        virtual void acceptReceipt( const std::array<uint8_t,32>&  downloadChannelId,
                                    const std::array<uint8_t,32>&  clientPublicKey,
                                    uint64_t                       downloadedSize,
                                    const std::array<uint8_t,64>&  signature,
                                    bool&                          shouldBeDisconnected,
                                    lt::errors::error_code_enum&   outErrorCode )
        {
            // now 'client' does nothing in this case
        }
    
        // It will be used in handshake (when client downloads torrent)
        //
        virtual const std::vector<uint8_t>* getLastClientReceipt( const std::array<uint8_t,32>&  downloadChannelId,
                                                                  const std::array<uint8_t,32>&  clientPublicKey )
        {
            // will be implemented by DownloadLimiter
            return nullptr;
        }

        virtual void onLastMyReceipt( const std::vector<uint8_t>, const std::unique_ptr<std::array<uint8_t,32>>& channelId )
        {
            // will be implemented by Client
        }

        // It will be used when client request piece
        //
        virtual uint64_t requestedSize( const std::array<uint8_t,32>&  transactionHash,
                                        const std::array<uint8_t,32>&  peerPublicKey )  = 0;

        virtual uint64_t receivedSize( const std::array<uint8_t,32>&  transactionHash,
                                       const std::array<uint8_t,32>&  peerPublicKey ) = 0;

    // Replicator/Client public key
        virtual const std::array<uint8_t,32>& publicKey() = 0;

        // Endpoint associated with the key
        virtual std::optional<boost::asio::ip::udp::endpoint> getEndpoint( const std::array<uint8_t,32>& key ) = 0;

        // It will be called when 'replicator' answers to 'client' (extended handshake)
        //virtual uint64_t receivedSize( const std::array<uint8_t,32>& downloadChannelId ) = 0;

        // It will be called when 'client' receives an answer from 'replicator' (extended handshake)
        // 'downloadedSize' should be set to proper value (last 'downloadedSize' of peviuos peer_connection)
        //virtual void setStartReceivedSize( uint64_t downloadedSize ) = 0;

        // They will be called when 'client' requests a piece fromonPieceReceived 'replicator' (handshake)
//        virtual uint64_t receivedSize( const std::array<uint8_t,32>&  transactionHash,
//                                       const std::array<uint8_t,32>&  peerPublicKey ) = 0;
        virtual void     handleDhtResponse( lt::bdecode_node response, boost::asio::ip::udp::endpoint endpoint ) = 0;

        virtual bool     isStopped()
        {
            return false;
        }

        virtual void      onError( lt::close_reason_t            errorCode,
                                   const std::array<uint8_t,32>& replicatorKey,
                                   const std::array<uint8_t,32>& channelHash,
                                   const std::array<uint8_t,32>& infoHash )
        {
            // must be emplemented by Client
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
