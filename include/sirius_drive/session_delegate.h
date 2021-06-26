/*
*** Copyright 2021 ProximaX Limited. All rights reserved.
*** Use of this source code is governed by the Apache 2.0
*** license that can be found in the LICENSE file.
*/
#pragma once

#include "libtorrent/sha1_hash.hpp"
#include <vector>

namespace libtorrent {

    class session_delegate {
    public:
        virtual ~session_delegate() = default;

        virtual bool checkDownloadLimit( std::vector<uint8_t> reciept,
                                         sha256_hash downloadChannelId,
                                         size_t downloadedSize ) = 0;
    };

};
