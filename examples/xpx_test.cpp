#include <cstdlib>

#include "libtorrent/entry.hpp"
#include "libtorrent/bencode.hpp"
#include "libtorrent/session.hpp"
#include "libtorrent/torrent_info.hpp"

#include <libtorrent/alert.hpp>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/hex.hpp>
#include <libtorrent/create_torrent.hpp>
#include <libtorrent/torrent_flags.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>

#include <iostream>
#include <filesystem>

int main() try
{

    std::string fileOrFolder = "/Users/alex/000/zip.zip";

    lt::file_storage fStorage;
    lt::add_files( fStorage, fileOrFolder, lt::create_flags_t{} );

    // create torrent info
    lt::create_torrent createInfo( fStorage, 16*1024, lt::create_torrent::v2_only );

    // calculate hashes for 'fileOrFolder' relative to 'rootFolder'
//    lt::error_code ec;
//    lt::set_piece_hashes( createInfo, rootFolder, ec );
//    std::cout << ec.category().name() << ':' << ec.value();
    lt::set_piece_hashes( createInfo, "/Users/alex/000" );

    // generate metadata
    lt::entry entry_info = createInfo.generate();

    // convert to bencoding
    std::vector<char> torrentFileBytes;
    entry_info["info"].dict()["xpx"]=lt::entry("pub_key");
    lt::bencode(std::back_inserter(torrentFileBytes), entry_info); // metainfo -> binary

    //dbg////////////////////////////////
    auto entry = entry_info;
    std::cout << "entry[info]:" << entry["info"].to_string() << std::endl;
    //LOG( entry.to_string() );
    auto tInfo = lt::torrent_info(torrentFileBytes, lt::from_span);
    //LOG( "make_magnet_uri:" << lt::make_magnet_uri(tInfo) );
    //dbg////////////////////////////////

    // get infoHash
    lt::torrent_info torrentInfo( torrentFileBytes, lt::from_span );
    auto binaryString = torrentInfo.info_hashes().v2.to_string();

    // copy hash
    std::array<uint8_t,32> infoHash;
    if ( binaryString.size()==32 ) {
        memcpy( &infoHash[0], &binaryString[0], 32 );
    }

    // write to file
//      fileStream( "/Users/alex/000/zip.zip.torrent", std::ios::binary );
//    fileStream.write(torrentFileBytes.data(),torrentFileBytes.size());

    return 0;
}
catch (std::exception const& e) {
    std::cerr << "ERROR: " << e.what() << "\n";
}
