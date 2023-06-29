cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR) # Configurable policies: <= CMP0097

cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0092 NEW)
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW) 
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_definitions(-w)
add_definitions(-DSIRIUS_INTEREST_MESSAGE_ENABLED)
add_definitions(-DSIRIUS_CHOKE_MESSAGE_ENABLED)
add_definitions(-DTORRENT_USE_RTC)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
include(LibtorrentMacros)

read_version("${CMAKE_CURRENT_SOURCE_DIR}/include/libtorrent/version.hpp" VER_MAJOR VER_MINOR VER_TINY)

project(libtorrent
	DESCRIPTION "Bittorrent library"
	VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_TINY}
)
set (SOVERSION "${VER_MAJOR}.${VER_MINOR}")

include(GNUInstallDirs)
include(GeneratePkgConfig)

option(SIRIUS_DRIVE "changes for sirius drive" ON)
if (SIRIUS_DRIVE)
	add_definitions(-DSIRIUS_DRIVE)
endif()

 option(SIRIUS_DRIVE_MULTI "changes for sirius drive-multi" ON)
 if (SIRIUS_DRIVE_MULTI)
 	add_definitions(-DSIRIUS_DRIVE_MULTI)
 endif()

set(libtorrent_include_files
	add_torrent_params.hpp
	address.hpp
	alert.hpp
	alert_types.hpp
	announce_entry.hpp
	assert.hpp
	bdecode.hpp
	bencode.hpp
	bitfield.hpp
	bloom_filter.hpp
	bt_peer_connection.hpp
	choker.hpp
	client_data.hpp
	close_reason.hpp
	config.hpp
	ConvertUTF.h
	copy_ptr.hpp
	crc32c.hpp
	create_torrent.hpp
	deadline_timer.hpp
	debug.hpp
	disk_buffer_holder.hpp
	disk_interface.hpp
	disk_observer.hpp
	download_priority.hpp
	entry.hpp
	enum_net.hpp
	error.hpp
	error_code.hpp
	extensions.hpp
	file.hpp
	file_storage.hpp
	fingerprint.hpp
	flags.hpp
	fwd.hpp
	gzip.hpp
	hash_picker.hpp
	hasher.hpp
	hex.hpp
	http_connection.hpp
	http_parser.hpp
	http_seed_connection.hpp
	http_stream.hpp
	http_tracker_connection.hpp
	i2p_stream.hpp
	identify_client.hpp
	index_range.hpp
	io.hpp
	io_service.hpp
	ip_filter.hpp
	ip_voter.hpp
	libtorrent.hpp
	link.hpp
	lsd.hpp
	magnet_uri.hpp
	mmap_disk_io.hpp
	mmap_storage.hpp
	natpmp.hpp
	netlink.hpp
	operations.hpp
	optional.hpp
	parse_url.hpp
	part_file.hpp
	peer.hpp
	peer_class.hpp
	peer_class_set.hpp
	peer_class_type_filter.hpp
	peer_connection.hpp
	peer_connection_handle.hpp
	peer_connection_interface.hpp
	peer_id.hpp
	peer_info.hpp
	peer_list.hpp
	peer_request.hpp
	performance_counters.hpp
	pex_flags.hpp
	piece_block.hpp
	piece_block_progress.hpp
	piece_picker.hpp
	platform_util.hpp
	portmap.hpp
	proxy_base.hpp
	puff.hpp
	random.hpp
	read_resume_data.hpp
	request_blocks.hpp
	resolve_links.hpp
	session.hpp
	session_handle.hpp
	session_params.hpp
	session_settings.hpp
	session_stats.hpp
	session_status.hpp
	session_types.hpp
	settings_pack.hpp
	sha1.hpp
	sha1_hash.hpp
	sha256.hpp
	sliding_average.hpp
	socket.hpp
	socket_io.hpp
	socket_type.hpp
	socks5_stream.hpp
	span.hpp
	ssl.hpp
	ssl_stream.hpp
	stack_allocator.hpp
	stat.hpp
	stat_cache.hpp
	storage_defs.hpp
	string_util.hpp
	string_view.hpp
	tailqueue.hpp
	time.hpp
	torrent.hpp
	torrent_flags.hpp
	torrent_handle.hpp
	torrent_info.hpp
	torrent_peer.hpp
	torrent_peer_allocator.hpp
	torrent_status.hpp
	tracker_manager.hpp
	udp_socket.hpp
	udp_tracker_connection.hpp
	union_endpoint.hpp
	units.hpp
	upnp.hpp
	vector_utils.hpp
	version.hpp
	web_connection_base.hpp
	web_peer_connection.hpp
	write_resume_data.hpp
	xml_parse.hpp
)

set(libtorrent_kademlia_include_files
	announce_flags.hpp
	dht_observer.hpp
	dht_settings.hpp
	dht_state.hpp
	dht_storage.hpp
	dht_tracker.hpp
	direct_request.hpp
	dos_blocker.hpp
	ed25519.hpp
	find_data.hpp
	get_item.hpp
	get_peers.hpp
	io.hpp
	item.hpp
	msg.hpp
	node.hpp
	node_entry.hpp
	node_id.hpp
	observer.hpp
	put_data.hpp
	refresh.hpp
	routing_table.hpp
	rpc_manager.hpp
	sample_infohashes.hpp
	traversal_algorithm.hpp
	types.hpp
)

set(libtorrent_extensions_include_files
	smart_ban.hpp
	ut_metadata.hpp
	ut_pex.hpp
)

set(libtorrent_aux_include_files
	alert_manager.hpp
	aligned_storage.hpp
	aligned_union.hpp
	alloca.hpp
	allocating_handler.hpp
	apply_pad_files.hpp
	array.hpp
	bandwidth_limit.hpp
	bandwidth_manager.hpp
	bandwidth_queue_entry.hpp
	bandwidth_socket.hpp
	bind_to_device.hpp
	buffer.hpp
	byteswap.hpp
	chained_buffer.hpp
	cpuid.hpp
	deferred_handler.hpp
	deprecated.hpp
	deque.hpp
	dev_random.hpp
	directory.hpp
	disable_warnings_pop.hpp
	disable_warnings_push.hpp
	disk_buffer_pool.hpp
	disk_io_job.hpp
	disk_io_thread_pool.hpp
	disk_job_fence.hpp
	disk_job_pool.hpp
	ed25519.hpp
	escape_string.hpp
	export.hpp
	ffs.hpp
	file_progress.hpp
	file_view_pool.hpp
	has_block.hpp
	heterogeneous_queue.hpp
	instantiate_connection.hpp
	invariant_check.hpp
	io.hpp
	ip_helpers.hpp
	ip_notifier.hpp
	keepalive.hpp
	listen_socket_handle.hpp
	lsd.hpp
	merkle.hpp
	merkle_tree.hpp
	noexcept_movable.hpp
	numeric_cast.hpp
	packet_buffer.hpp
	packet_pool.hpp
	path.hpp
	polymorphic_socket.hpp
	pool.hpp
	portmap.hpp
	posix_part_file.hpp
	proxy_settings.hpp
	range.hpp
	receive_buffer.hpp
	resolver.hpp
	resolver_interface.hpp
	scope_end.hpp
	session_call.hpp
	session_impl.hpp
	session_interface.hpp
	session_settings.hpp
	session_udp_sockets.hpp
	set_socket_buffer.hpp
	socket_type.hpp
	storage_free_list.hpp
	storage_utils.hpp
	string_ptr.hpp
	strview_less.hpp
	suggest_piece.hpp
	throw.hpp
	time.hpp
	timestamp_history.hpp
	torrent_impl.hpp
	torrent_list.hpp
	unique_ptr.hpp
	utp_socket_manager.hpp
	utp_stream.hpp
	vector.hpp
	win_crypto_provider.hpp
	win_util.hpp
	rtc_signaling.hpp
	rtc_stream.hpp
	websocket_stream.hpp
	websocket_tracker_connection.hpp
	utf8.hpp
)

set(try_signal_include_files
	try_signal
	signal_error_code
	try_signal_mingw
	try_signal_msvc
	try_signal_posix
)

set(sources
	add_torrent_params.cpp
	alert.cpp
	alert_manager.cpp
	announce_entry.cpp
	assert.cpp
	bandwidth_limit.cpp
	bandwidth_manager.cpp
	bandwidth_queue_entry.cpp
	bdecode.cpp
	bitfield.cpp
	bloom_filter.cpp
	bt_peer_connection.cpp
	chained_buffer.cpp
	choker.cpp
	close_reason.cpp
	cpuid.cpp
	crc32c.cpp
	create_torrent.cpp
	directory.cpp
	disabled_disk_io.cpp
	disk_buffer_holder.cpp
	disk_buffer_pool.cpp
	disk_interface.cpp
	disk_io_job.cpp
	disk_io_thread_pool.cpp
	disk_job_fence.cpp
	disk_job_pool.cpp
	entry.cpp
	enum_net.cpp
	error_code.cpp
	escape_string.cpp
	ffs.cpp
	file.cpp
	file_progress.cpp
	file_storage.cpp
	file_view_pool.cpp
	fingerprint.cpp
	generate_peer_id.cpp
	gzip.cpp
	hash_picker.cpp
	hasher.cpp
	hex.cpp
	http_connection.cpp
	http_parser.cpp
	http_seed_connection.cpp
	http_tracker_connection.cpp
	i2p_stream.cpp
	identify_client.cpp
	instantiate_connection.cpp
	ip_filter.cpp
	ip_helpers.cpp
	ip_notifier.cpp
	ip_voter.cpp
	listen_socket_handle.cpp
	lsd.cpp
	magnet_uri.cpp
	merkle.cpp
	merkle_tree.cpp
	mmap.cpp
	mmap_disk_io.cpp
	mmap_storage.cpp
	natpmp.cpp
	packet_buffer.cpp
	parse_url.cpp
	part_file.cpp
	path.cpp
	peer_class.cpp
	peer_class_set.cpp
	peer_connection.cpp
	peer_connection_handle.cpp
	peer_info.cpp
	peer_list.cpp
	performance_counters.cpp
	piece_picker.cpp
	platform_util.cpp
	posix_disk_io.cpp
	posix_part_file.cpp
	posix_storage.cpp
	rtc_signaling.cpp
	rtc_stream.cpp
	websocket_stream.cpp
	websocket_tracker_connection.cpp
	proxy_base.cpp
	proxy_settings.cpp
	puff.cpp
	random.cpp
	read_resume_data.cpp
	receive_buffer.cpp
	request_blocks.cpp
	resolve_links.cpp
	resolver.cpp
	session.cpp
	session_call.cpp
	session_handle.cpp
	session_impl.cpp
	session_params.cpp
	session_settings.cpp
	session_stats.cpp
	settings_pack.cpp
	sha1.cpp
	sha1_hash.cpp
	sha256.cpp
	socket_io.cpp
	socket_type.cpp
	socks5_stream.cpp
	ssl.cpp
	stack_allocator.cpp
	stat.cpp
	stat_cache.cpp
	storage_utils.cpp
	string_util.cpp
	time.cpp
	timestamp_history.cpp
	torrent.cpp
	torrent_handle.cpp
	torrent_info.cpp
	torrent_peer.cpp
	torrent_peer_allocator.cpp
	torrent_status.cpp
	tracker_manager.cpp
	udp_socket.cpp
	udp_tracker_connection.cpp
	upnp.cpp
	utf8.cpp
	utp_socket_manager.cpp
	utp_stream.cpp
	version.cpp
	web_connection_base.cpp
	web_peer_connection.cpp
	write_resume_data.cpp
	xml_parse.cpp

# -- extensions --
	smart_ban.cpp
	ut_pex.cpp
	ut_metadata.cpp
)

# -- kademlia --
set(kademlia_sources
	dht_settings.cpp
	dht_state.cpp
	dht_storage.cpp
	dht_tracker.cpp
	dos_blocker.cpp
	ed25519.cpp
	find_data.cpp
	get_item.cpp
	get_peers.cpp
	item.cpp
	msg.cpp
	node.cpp
	node_entry.cpp
	node_id.cpp
	put_data.cpp
	refresh.cpp
	routing_table.cpp
	rpc_manager.cpp
	sample_infohashes.cpp
	traversal_algorithm.cpp
)

# -- ed25519 --
set(ed25519_sources
	add_scalar.cpp
	fe.cpp
	ge.cpp
	key_exchange.cpp
	keypair.cpp
	sc.cpp
	sign.cpp
	verify.cpp
	sha512.cpp
	hasher512.cpp
)

set(try_signal_sources
	try_signal.cpp
	signal_error_code.cpp
)

set(datachannel_juice_sources
		ice.c
		const_time.c
		hash.c
		log.c
		conn_thread.c
		udp.c
		crc32.c
		timestamp.c
		hmac.c
		server.c
		juice.c
		turn.c
		stun.c
		random.c
		conn_poll.c
		conn_mux.c
		conn.c
		base64.c
		agent.c
		addr.c
)

set(datachannel_juice_headers
		juice.h
)

set(datachannel_srtp_sources
  srtp/srtp.c
)

set(datachannel_srtp_crypto_cipher_sources
  crypto/cipher/cipher.cpp
  crypto/cipher/null_cipher.cpp
)

if(ENABLE_OPENSSL)
  list(APPEND datachannel_srtp_crypto_cipher_sources
    crypto/cipher/aes_icm_ossl.cpp
    crypto/cipher/aes_gcm_ossl.cpp
  )
else()
  list(APPEND datachannel_srtp_crypto_cipher_sources
    crypto/cipher/aes.cpp
    crypto/cipher/aes_icm.cpp
  )
endif()

set(datachannel_srtp_crypto_hashes_sources
    crypto/hash/auth.cpp
    crypto/hash/null_auth.cpp
)

if(ENABLE_OPENSSL)
  list(APPEND datachannel_srtp_crypto_hashes_sources
    crypto/hash/hmac_ossl.cpp
  )
else()
  list(APPEND  datachannel_srtp_crypto_hashes_sources
    crypto/hash/hmac.cpp
    crypto/hash/sha1.cpp
  )
endif()

set(datachannel_srtp_crypto_kernel_sources
  crypto/kernel/alloc.cpp
  crypto/kernel/crypto_kernel.cpp
  crypto/kernel/err.cpp
  crypto/kernel/key.cpp
)

set(datachannel_srtp_crypto_math_sources
  crypto/math/datatypes.cpp
  crypto/math/stat.cpp
)

set(datachannel_srtp_crypto_replay_sources
  crypto/replay/rdb.cpp
  crypto/replay/rdbx.cpp
  crypto/replay/ut_sim.cpp
)

set(datachannel_srtp_config_header
	config.h
)

set(datachannel_srtp_headers
  crypto/include/aes.h
  crypto/include/aes_icm.h
  crypto/include/alloc.h
  crypto/include/auth.h
  crypto/include/cipher.h
  crypto/include/cipher_types.h
  crypto/include/crypto_kernel.h
  crypto/include/crypto_types.h
  crypto/include/datatypes.h
  crypto/include/err.h
  crypto/include/hmac.h
  crypto/include/integers.h
  crypto/include/key.h
  crypto/include/null_auth.h
  crypto/include/null_cipher.h
  crypto/include/rdb.h
  crypto/include/rdbx.h
  crypto/include/sha1.h
  include/srtp.h
  include/srtp_priv.h
)

set(datachannel_usrsctp_sources
		user_environment.c
		user_mbuf.c
		user_recv_thread.c
		user_socket.c
)

set(datachannel_headers
		candidate.hpp
		channel.hpp
		common.hpp
		configuration.hpp
		datachannel.hpp
		description.hpp
		global.hpp
		h264packetizationhandler.hpp
		h264rtppacketizer.hpp
		mediachainablehandler.hpp
		mediahandler.hpp
		mediahandlerelement.hpp
		mediahandlerrootelement.hpp
		message.hpp
		nalunit.hpp
		opuspacketizationhandler.hpp
		opusrtppacketizer.hpp
		peerconnection.hpp
		reliability.hpp
		rtc.h
		rtc.hpp
		rtcpnackresponder.hpp
		rtcpreceivingsession.hpp
		rtcpsrreporter.hpp
		rtp.hpp
		rtppacketizationconfig.hpp
		rtppacketizer.hpp
		track.hpp
		utils.hpp
		websocket.hpp
		websocketserver.hpp
)

set(datachannel_sources
		candidate.cpp
		capi.cpp
		channel.cpp
		configuration.cpp
		datachannel.cpp
		description.cpp
		global.cpp
		h264packetizationhandler.cpp
		h264rtppacketizer.cpp
		mediachainablehandler.cpp
		mediahandlerelement.cpp
		mediahandlerrootelement.cpp
		message.cpp
		nalunit.cpp
		opuspacketizationhandler.cpp
		opusrtppacketizer.cpp
		peerconnection.cpp
		rtcpnackresponder.cpp
		rtcpreceivingsession.cpp
		rtcpsrreporter.cpp
		rtp.cpp
		rtppacketizationconfig.cpp
		rtppacketizer.cpp
		track.cpp
		websocket.cpp
		websocketserver.cpp
)

set(datachannel_headers_impl
		certificate.hpp
		channel.hpp
		datachannel.hpp
		dtlssrtptransport.hpp
		dtlstransport.hpp
		icetransport.hpp
		init.hpp
		internals.hpp
		logcounter.hpp
		peerconnection.hpp
		pollinterrupter.hpp
		pollservice.hpp
		processor.hpp
		queue.hpp
		sctptransport.hpp
		sha.hpp
		tcpserver.hpp
		tcptransport.hpp
		socket.hpp
		threadpool.hpp
		tls.hpp
		tlstransport.hpp
		track.hpp
		transport.hpp
		utils.hpp
		verifiedtlstransport.hpp
		websocket.hpp
		websocketserver.hpp
		wshandshake.hpp
		wstransport.hpp
)

set(datachannel_sources_impl
		track.cpp
		websocketserver.cpp
		tcpserver.cpp
		wstransport.cpp
		transport.cpp
		tlstransport.cpp
		verifiedtlstransport.cpp
		utils.cpp
		wshandshake.cpp
		threadpool.cpp
		tls.cpp
		websocket.cpp
		tcptransport.cpp
		sctptransport.cpp
		sha.cpp
		processor.cpp
		pollservice.cpp
		pollinterrupter.cpp
		peerconnection.cpp
		logcounter.cpp
		init.cpp
		icetransport.cpp
		dtlstransport.cpp
		dtlssrtptransport.cpp
		datachannel.cpp
		channel.cpp
		certificate.cpp
)

set(sirius_drive
	session_delegate.h
)

list(TRANSFORM sources PREPEND "src/")
list(TRANSFORM kademlia_sources PREPEND "src/kademlia/")
list(TRANSFORM ed25519_sources PREPEND "src/ed25519/")
list(TRANSFORM libtorrent_include_files PREPEND "include/libtorrent/")
list(TRANSFORM libtorrent_extensions_include_files PREPEND "include/libtorrent/extensions/")
list(TRANSFORM libtorrent_aux_include_files PREPEND "include/libtorrent/aux_/")
list(TRANSFORM libtorrent_kademlia_include_files PREPEND "include/libtorrent/kademlia/")

list(TRANSFORM try_signal_sources PREPEND "deps/try_signal/")

list(TRANSFORM datachannel_juice_sources PREPEND "deps/libdatachannel/deps/libjuice/src/")
list(TRANSFORM datachannel_juice_headers PREPEND "deps/libdatachannel/deps/libjuice/include/juice/")
list(TRANSFORM datachannel_srtp_sources PREPEND "deps/libdatachannel/deps/libsrtp/")
list(TRANSFORM datachannel_srtp_headers PREPEND "deps/libdatachannel/deps/libsrtp/")
list(TRANSFORM datachannel_srtp_crypto_cipher_sources PREPEND "deps/libdatachannel/deps/libsrtp/")
list(TRANSFORM datachannel_srtp_crypto_hashes_sources PREPEND "deps/libdatachannel/deps/libsrtp/")
list(TRANSFORM datachannel_srtp_crypto_kernel_sources PREPEND "deps/libdatachannel/deps/libsrtp/")
list(TRANSFORM datachannel_srtp_crypto_math_sources PREPEND "deps/libdatachannel/deps/libsrtp/")
list(TRANSFORM datachannel_srtp_crypto_replay_sources PREPEND "deps/libdatachannel/deps/libsrtp/")
list(TRANSFORM datachannel_srtp_config_header PREPEND "${CONFIG_FILE_DIR}")
list(TRANSFORM datachannel_usrsctp_sources PREPEND "deps/libdatachannel/deps/usrsctp/usrsctplib/")
list(TRANSFORM datachannel_headers PREPEND "deps/libdatachannel/include/rtc/")
list(TRANSFORM datachannel_sources PREPEND "deps/libdatachannel/src/")
list(TRANSFORM datachannel_headers_impl PREPEND "deps/libdatachannel/src/impl/")
list(TRANSFORM datachannel_sources_impl PREPEND "deps/libdatachannel/src/impl/")

list(TRANSFORM sirius_drive PREPEND "include/sirius_drive/")

# these options control target creation and thus have to be declared before the add_library() call
feature_option(TORRENT_SHARED_LIB "build libtorrent as a shared library" ON)
feature_option(static_runtime "build libtorrent with static runtime" OFF)

find_public_dependency(Threads REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
		-Weverything \
		-Wno-documentation \
		-Wno-c++98-compat-pedantic \
		-Wno-padded \
		-Wno-global-constructors \
		-Wno-exit-time-destructors \
		-Wno-weak-vtables \
		-Wno-return-std-move-in-c++11 \
		-Wno-unknown-warning-option \
		-fpermissive")
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
		-Wall \
		-Wextra \
		-Wpedantic \
		-Wparentheses \
		-Wvla \
		-Wc++11-compat \
		-Wno-format-zero-length \
		-Wno-noexcept-type \
		-ftemplate-depth=512 \
		-fpermissive")
elseif(MSVC)
	add_compile_options(
		# https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
		/Zc:__cplusplus
		/W4
		# C4251: 'identifier' : class 'type' needs to have dll-interface to be
		#        used by clients of class 'type2'
		/wd4251
		# C4268: 'identifier' : 'const' static/global data initialized
		#        with compiler generated default constructor fills the object with zeros
		/wd4268
		# C4275: non DLL-interface classkey 'identifier' used as base for
		#        DLL-interface classkey 'identifier'
		/wd4275
		# C4373: virtual function overrides, previous versions of the compiler
		#        did not override when parameters only differed by const/volatile qualifiers
		/wd4373
		# C4503: 'identifier': decorated name length exceeded, name was truncated
		/wd4503
	)
endif()

if(static_runtime)
	if (MSVC)
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	else()
		include(ucm_flags)
		ucm_set_runtime(STATIC)
	endif()
	set(Boost_USE_MULTITHREADED ON)
	set(Boost_USE_STATIC_RUNTIME ON)
	set(OPENSSL_MSVC_STATIC_RT ON)
endif()

if (NOT TORRENT_SHARED_LIB)
	set(Boost_USE_STATIC_LIBS ON)
	set(OPENSSL_USE_STATIC_LIBS ON)
endif()

set(BUILD_SHARED_LIBS_COPY BUILD_SHARED_LIBS)
set(BUILD_SHARED_LIBS TORRENT_SHARED_LIB)
add_library(torrent-sirius
	${sources}
	${try_signal_sources}
	${datachannel_juice_sources}
	${datachannel_juice_headers}
	${datachannel_srtp_sources}
	${datachannel_srtp_headers}
	${datachannel_srtp_config_header}
	${datachannel_usrsctp_sources}
	${datachannel_headers}
	${datachannel_sources}
	${datachannel_headers_impl}
	${datachannel_sources_impl}
	${libtorrent_include_files}
	${libtorrent_extensions_include_files}
	${libtorrent_aux_include_files}
	${sirius_drive}
)
set(BUILD_SHARED_LIBS BUILD_SHARED_LIBS_COPY)

# C++ 14 support is required
target_compile_features(torrent-sirius
	PUBLIC
		cxx_std_14
		cxx_attribute_deprecated
		cxx_binary_literals
		cxx_contextual_conversions
		cxx_decltype_auto
		cxx_digit_separators
		cxx_generic_lambdas
		cxx_lambda_init_captures
		cxx_relaxed_constexpr
		cxx_variable_templates
)

if (TORRENT_SHARED_LIB)
	target_compile_definitions(torrent-sirius
		PRIVATE TORRENT_BUILDING_SHARED
		INTERFACE TORRENT_LINKING_SHARED
	)
endif()

set_target_properties(torrent-sirius
	PROPERTIES
		CXX_VISIBILITY_PRESET "hidden"
		VISIBILITY_INLINES_HIDDEN "true"
		VERSION ${PROJECT_VERSION}
		SOVERSION ${SOVERSION}
)

target_include_directories(torrent-sirius PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	PRIVATE deps/libdatachannel/deps/libjuice/include
	PRIVATE deps/libdatachannel/deps/libjuice/include/juice
	PRIVATE ${CONFIG_FILE_DIR}/
	PRIVATE deps/libdatachannel/deps/libsrtp/crypto/include
	PRIVATE deps/libdatachannel/deps/libsrtp/include
	PRIVATE deps/libdatachannel/deps/plog/include
	PRIVATE deps/libdatachannel/deps/usrsctp/usrsctplib
	PRIVATE deps/libdatachannel/include
	PRIVATE deps/libdatachannel/include/rtc
	PRIVATE deps/try_signal
)

target_compile_definitions(torrent-sirius
	PUBLIC
		$<$<CONFIG:Debug>:TORRENT_USE_ASSERTS>
		BOOST_ASIO_ENABLE_CANCELIO
		BOOST_ASIO_NO_DEPRECATED
	PRIVATE
		TORRENT_BUILDING_LIBRARY
		_FILE_OFFSET_BITS=64
		BOOST_EXCEPTION_DISABLE
		BOOST_ASIO_HAS_STD_CHRONO
)

target_link_libraries(torrent-sirius
	PUBLIC
		Threads::Threads
)

# Unconditional platform-specific settings
if (WIN32)
	target_link_libraries(torrent-sirius
		PUBLIC
			bcrypt mswsock ws2_32 iphlpapi
			debug dbghelp crypt32
	)

	add_definitions(-D_WIN32_WINNT=0x0600) # target Windows Vista or later

	target_compile_definitions(torrent-sirius
		PUBLIC WIN32_LEAN_AND_MEAN # prevent winsock1 to be included
	)

	if (MSVC)
		target_compile_definitions(torrent-sirius
			PUBLIC
				BOOST_ALL_NO_LIB
				_SCL_SECURE_NO_DEPRECATE _CRT_SECURE_NO_DEPRECATE # disable bogus deprecation warnings on msvc8
		)
		target_compile_options(torrent-sirius
			PRIVATE
				/Zc:wchar_t /Zc:forScope # these compiler settings just make the compiler standard conforming
				/MP # for multi-core compilation
				/bigobj # increase the number of sections for obj files
		)
		set_target_properties(torrent-sirius PROPERTIES LINK_FLAGS_RELEASE "/OPT:ICF=5 /OPT:REF")
	endif()
endif()

if (ANDROID)
	target_link_libraries(torrent-sirius PRIVATE ${CMAKE_DL_LIBS})
endif()

if (APPLE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
	set(BOOST_INCLUDE_DIR "/usr/local/include")
	set(BOOST_LIB_DIR "/usr/local/lib")
	set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
	set(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")

    # for ip_notifier
    target_link_libraries(torrent-sirius PRIVATE "-framework CoreFoundation" "-framework SystemConfiguration")
endif()

# check if we need to link with libatomic (not needed on MSVC)
if (NOT Windows)
	# TODO: migrate to CheckSourceCompiles in CMake >= 3.19
	include(CheckCXXSourceCompiles)

	set(ATOMICS_TEST_SOURCE [=[
		#include <atomic>
		#include <cstdint>
		std::atomic<int> x{0};
		int main() {
			x.fetch_add(1, std::memory_order_relaxed);
			return 0;
		}
	]=])
	string(REPLACE "std::atomic<int>" "std::atomic<std::int64_t>" ATOMICS64_TEST_SOURCE "${ATOMICS_TEST_SOURCE}")

	if(APPLE)
		set(CMAKE_REQUIRED_FLAGS "-std=c++14")
	endif()
	check_cxx_source_compiles("${ATOMICS_TEST_SOURCE}" HAVE_CXX_ATOMICS_WITHOUT_LIB)
	check_cxx_source_compiles("${ATOMICS64_TEST_SOURCE}" HAVE_CXX_ATOMICS64_WITHOUT_LIB)
	if((NOT HAVE_CXX_ATOMICS_WITHOUT_LIB) OR (NOT HAVE_CXX_ATOMICS64_WITHOUT_LIB))
		set(CMAKE_REQUIRED_LIBRARIES "atomic")
		check_cxx_source_compiles("${ATOMICS_TEST_SOURCE}" HAVE_CXX_ATOMICS_WITH_LIB)
		check_cxx_source_compiles("${ATOMICS64_TEST_SOURCE}" HAVE_CXX_ATOMICS64_WITH_LIB)
		if ( (NOT APPLE) AND ((NOT HAVE_CXX_ATOMICS_WITH_LIB) OR (NOT HAVE_CXX_ATOMICS64_WITH_LIB)))
			message(FATAL_ERROR "No native support for std::atomic, or libatomic not found!")
		else()
			message(STATUS "Linking with libatomic for atomics support")
			unset(CMAKE_REQUIRED_LIBRARIES)
			#target_link_libraries(torrent-sirius PUBLIC atomic)
		endif()
	endif()
	if(APPLE)
		unset(CMAKE_REQUIRED_FLAGS)
	endif()
endif()

feature_option(build_tests "build tests" OFF)
feature_option(build_examples "build examples" OFF)
feature_option(build_tools "build tools" OFF)
feature_option(python-bindings "build python bindings" OFF)
feature_option(python-egg-info "generate python egg info" OFF)
feature_option(python-install-system-dir "Install python bindings to the system installation directory rather than the CMake installation prefix" OFF)

# these options require existing target
feature_option(dht "enable support for Mainline DHT" ON)
target_optional_compile_definitions(torrent-sirius PUBLIC FEATURE NAME deprecated-functions DEFAULT ON
	DESCRIPTION "enable deprecated functions for backwards compatibility" DISABLED TORRENT_NO_DEPRECATE)
feature_option(encryption "Enables encryption in libtorrent" ON)
feature_option(exceptions "build with exception support" ON)
feature_option(gnutls "build using GnuTLS instead of OpenSSL" OFF)
target_optional_compile_definitions(torrent-sirius PUBLIC FEATURE NAME extensions DEFAULT ON
	DESCRIPTION "Enables protocol extensions" DISABLED TORRENT_DISABLE_EXTENSIONS)
target_optional_compile_definitions(torrent-sirius PUBLIC FEATURE NAME i2p DEFAULT ON
	DESCRIPTION "build with I2P support" DISABLED TORRENT_USE_I2P=0)
target_optional_compile_definitions(torrent-sirius PUBLIC FEATURE NAME webtorrent DEFAULT ON
		DESCRIPTION "build with WebTorrent support" DISABLED TORRENT_USE_RTC=1)
target_optional_compile_definitions(torrent-sirius PUBLIC FEATURE NAME logging DEFAULT ON
	DESCRIPTION "build with logging" DISABLED TORRENT_DISABLE_LOGGING)
target_optional_compile_definitions(torrent-sirius PUBLIC FEATURE NAME mutable-torrents DEFAULT ON
	DESCRIPTION "Enables mutable torrent support" DISABLED TORRENT_DISABLE_MUTABLE_TORRENTS)
target_optional_compile_definitions(torrent-sirius PUBLIC FEATURE NAME streaming DEFAULT ON
	DESCRIPTION "Enables support for piece deadline" DISABLED TORRENT_DISABLE_STREAMING)

if(NOT gnutls)
	find_public_dependency(OpenSSL)
	set_package_properties(OpenSSL
		PROPERTIES
			URL "https://www.openssl.org/"
			DESCRIPTION "Full-strength general purpose cryptography library"
			TYPE RECOMMENDED
			PURPOSE "Provides HTTPS support to libtorrent"
	)

	if(TARGET OpenSSL::SSL)
		# TODO: needed until https://gitlab.kitware.com/cmake/cmake/issues/19263 is fixed
		if(WIN32 AND OPENSSL_USE_STATIC_LIBS)
			target_link_libraries(torrent-sirius PRIVATE crypt32)
		endif()
		target_link_libraries(torrent-sirius PUBLIC OpenSSL::SSL)
		target_compile_definitions(torrent-sirius
			PUBLIC
				TORRENT_USE_OPENSSL
				TORRENT_USE_LIBCRYPTO
				TORRENT_SSL_PEERS
				OPENSSL_NO_SSL2)
	endif()
endif()

if(gnutls OR NOT TARGET OpenSSL::SSL)
	find_public_dependency(GnuTLS)
	set_package_properties(GnuTLS
		PROPERTIES
			URL "https://www.gnutls.org/"
			DESCRIPTION "GnuTLS is a free software implementation of the TLS and DTLS protocols"
			TYPE RECOMMENDED
			PURPOSE "Provides HTTPS support to libtorrent"
	)
	if(GNUTLS_FOUND)
		target_link_libraries(torrent-sirius PUBLIC GnuTLS::GnuTLS)
		target_compile_definitions(torrent-sirius
			PUBLIC
				TORRENT_USE_GNUTLS
				TORRENT_SSL_PEERS)
		target_include_directories(torrent-sirius PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/deps/asio-gnutls/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
		install(DIRECTORY deps/asio-gnutls/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
	elseif(gnutls)
		message(FATAL_ERROR "GnuTLS library not found")
	endif()
endif()

if (NOT GNUTLS_FOUND AND NOT TARGET OpenSSL::SSL)
	if(TARGET OpenSSL::Crypto)
		target_link_libraries(torrent-sirius PUBLIC OpenSSL::Crypto)
		target_compile_definitions(torrent-sirius PUBLIC TORRENT_USE_LIBCRYPTO)
	else()
		find_public_dependency(LibGcrypt)
		set_package_properties(LibGcrypt
			PROPERTIES
				URL "https://www.gnupg.org/software/libgcrypt/index.html"
				DESCRIPTION "A general purpose cryptographic library"
				TYPE RECOMMENDED
				PURPOSE "Use GCrypt instead of the built-in functions for RC4 and SHA1"
		)
		if (LibGcrypt_FOUND)
			target_compile_definitions(torrent-sirius PUBLIC TORRENT_USE_LIBGCRYPT)
			target_link_libraries(torrent-sirius PRIVATE LibGcrypt::LibGcrypt)
		endif()
	endif()
endif()

if (encryption)
	target_sources(torrent-sirius PRIVATE include/libtorrent/pe_crypto.hpp src/pe_crypto.cpp)
else()
	target_compile_definitions(torrent-sirius PUBLIC TORRENT_DISABLE_ENCRYPTION)
endif()

if (dht)
	target_sources(torrent-sirius PRIVATE
		${libtorrent_kademlia_include_files}
		include/libtorrent/aux_/hasher512.hpp
		${kademlia_sources}
		${ed25519_sources}
	)
else()
	target_compile_definitions(torrent-sirius PUBLIC TORRENT_DISABLE_DHT)
endif()

if (webtorrent)
	find_package(OpenSSL REQUIRED)

	set(OPENSSL ${ENABLE_OPENSSL} CACHE BOOL INTERNAL)
	set(GCM ${ENABLE_OPENSSL} CACHE BOOL INTERNAL)
	set(CONFIG_FILE_DIR ${CMAKE_CURRENT_BINARY_DIR})

	add_definitions(-D__Userspace__)
	add_definitions(-DSCTP_SIMPLE_ALLOCATOR)
	add_definitions(-DSCTP_PROCESS_LEVEL_LOCKS)
	add_definitions(-DHAVE_CONFIG_H)

	include_directories(${CONFIG_FILE_DIR})
	include_directories(${OPENSSL_INCLUDE_DIR})

	check_include_file(arpa/inet.h HAVE_ARPA_INET_H)
	check_include_file(byteswap.h HAVE_BYTESWAP_H)
	check_include_file(inttypes.h HAVE_INTTYPES_H)
	check_include_file(machine/types.h HAVE_MACHINE_TYPES_H)
	check_include_file(netinet/in.h HAVE_NETINET_IN_H)
	check_include_file(stdint.h HAVE_STDINT_H)
	check_include_file(stdlib.h HAVE_STDLIB_H)
	check_include_file(sys/int_types.h HAVE_SYS_INT_TYPES_H)
	check_include_file(sys/socket.h HAVE_SYS_SOCKET_H)
	check_include_file(sys/types.h HAVE_SYS_TYPES_H)
	check_include_file(unistd.h HAVE_UNISTD_H)
	check_include_file(windows.h HAVE_WINDOWS_H)
	check_include_file(winsock2.h HAVE_WINSOCK2_H)
	check_c_source_compiles("inline void func(); void func() { } int main() { func(); return 0; }" HAVE_INLINE)
	configure_file(deps/libdatachannel/deps/libsrtp/config_in_cmake.h ${CONFIG_FILE_DIR}/config.h)


	if(NOT HAVE_INLINE)
	  check_c_source_compiles("__inline void func(); void func() { } int main() { func(); return 0; }" HAVE___INLINE)
	endif()

	if(GNUTLS_FOUND)
		option(USE_GNUTLS "Use GnuTLS instead of OpenSSL for libdatachannel" ON)
	else()
		option(USE_GNUTLS "Use GnuTLS instead of OpenSSL for libdatachannel" OFF)
	endif()

	option(USE_NETTLE "Use Nettle in libjuice" OFF)
	option(ENABLE_OPENSSL "Enable OpenSSL crypto engine for SRTP" ON)

	#add_subdirectory(deps/libdatachannel EXCLUDE_FROM_ALL)
	add_subdirectory(deps/libdatachannel/deps/libsrtp EXCLUDE_FROM_ALL)
	add_subdirectory(deps/libdatachannel/deps/libjuice EXCLUDE_FROM_ALL)

	target_compile_definitions(torrent-sirius PRIVATE USE_NICE=0)
	target_compile_definitions(torrent-sirius PRIVATE RTC_SYSTEM_SRTP=0)
	target_compile_definitions(torrent-sirius PRIVATE USE_GNUTLS=0)
endif()

# Boost
find_public_dependency(Boost REQUIRED)
target_include_directories(torrent-sirius PUBLIC ${Boost_INCLUDE_DIRS})
if (Boost_MAJOR_VERSION LESS_EQUAL 1 AND Boost_MINOR_VERSION LESS 69)
	find_package(Boost REQUIRED COMPONENTS system)
	target_link_libraries(torrent-sirius PUBLIC ${Boost_SYSTEM_LIBRARY})
endif()

if (exceptions)
	if (MSVC)
		target_compile_options(torrent-sirius PUBLIC /EHsc)
	else (MSVC)
		target_compile_options(torrent-sirius PUBLIC -fexceptions)
	endif (MSVC)
else()
	if (MSVC)
		target_compile_definitions(torrent-sirius PUBLIC _HAS_EXCEPTIONS=0)
	else (MSVC)
		target_compile_options(torrent-sirius PUBLIC -fno-exceptions)
	endif (MSVC)
endif()

# developer options
option(developer-options "Activates options useful for a developer")
if(developer-options)
	set(asserts "auto" CACHE STRING "use assertions")
	set_property(CACHE asserts PROPERTY STRINGS auto on off production system)
	if ("${asserts}" MATCHES "on|production|system")
		target_compile_definitions(torrent-sirius PUBLIC TORRENT_USE_ASSERTS=1)
	endif()
	if ("${asserts}" STREQUAL "production")
		target_compile_definitions(torrent-sirius PUBLIC TORRENT_PRODUCTION_ASSERTS=1)
	elseif("${asserts}" STREQUAL "system")
		target_compile_definitions(torrent-sirius PUBLIC TORRENT_USE_SYSTEM_ASSERTS=1)
	endif()

	target_optional_compile_definitions(torrent-sirius PUBLIC NAME asio-debugging DEFAULT OFF
		ENABLED TORRENT_ASIO_DEBUGGING)
	target_optional_compile_definitions(torrent-sirius PUBLIC NAME picker-debugging DEFAULT OFF
		ENABLED TORRENT_DEBUG_REFCOUNTS)
	set(invariant-checks "off" CACHE STRING "")
	set_property(CACHE invariant-checks PROPERTY STRINGS off on full)
	if (invariant-checks MATCHES "on|full")
		target_compile_definitions(torrent-sirius PUBLIC TORRENT_USE_INVARIANT_CHECKS=1)
	endif()
	if (invariant-checks STREQUAL "full")
		target_compile_definitions(torrent-sirius PUBLIC TORRENT_EXPENSIVE_INVARIANT_CHECKS)
	endif()

	target_optional_compile_definitions(torrent-sirius PUBLIC NAME utp-log DEFAULT OFF
		ENABLED TORRENT_UTP_LOG_ENABLE)
	target_optional_compile_definitions(torrent-sirius PUBLIC NAME simulate-slow-read DEFAULT OFF
		ENABLED TORRENT_SIMULATE_SLOW_READ)
	option(debug-iterators "" OFF)
	if (debug-iterators)
		if (MSVC)
			target_compile_definitions(torrent-sirius PUBLIC _ITERATOR_DEBUG_LEVEL=2)
		endif()
		if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
			target_compile_definitions(torrent-sirius PUBLIC _GLIBCXX_DEBUG _GLIBCXX_DEBUG_PEDANTIC)
		endif()
	endif()
	target_optional_compile_definitions(torrent-sirius PUBLIC NAME profile-calls DEFAULT OFF
		ENABLED TORRENT_PROFILE_CALLS=1)
endif()

# This is best effort attempt to propagate whether the library was built with
# C++11 or not. It affects the ABI of entry. A client building with C++14 and
# linking against a libtorrent binary built with C++11 can still define
# TORRENT_CXX11_ABI
if ("${CMAKE_CXX_STANDARD}" STREQUAL "11")
	target_compile_definitions(torrent-sirius PUBLIC TORRENT_CXX11_ABI)
endif()

# There is little to none support for using pkg-config with MSVC and most users won't bother with it.
# However, msys is a linux-like platform on Windows that do support/prefer using pkg-config.
if (NOT MSVC)
	generate_and_install_pkg_config_file(torrent-sirius sirius)
endif()

include(CheckCXXCompilerFlag)

add_subdirectory(bindings)

if(IS_ABSOLUTE "${CMAKE_INSTALL_LIBDIR}")
	file(RELATIVE_PATH CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_LIBDIR}")
endif()

install(TARGETS torrent-sirius EXPORT LibtorrentRasterbarTargets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/libtorrent DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h*")
install(DIRECTORY include/sirius_drive DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h*")

# === generate a CMake Config File ===
include(CMakePackageConfigHelpers)
set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/LibtorrentRasterbar)
string(REGEX REPLACE "([^;]+)" "find_dependency(\\1)" _find_dependency_calls "${_package_dependencies}")
string(REPLACE ";" "\n" _find_dependency_calls "${_find_dependency_calls}")

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/LibtorrentRasterbar/LibtorrentRasterbarConfigVersion.cmake"
	VERSION ${libtorrent_VERSION}
	COMPATIBILITY AnyNewerVersion
)

export(EXPORT LibtorrentRasterbarTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/LibtorrentRasterbar/LibtorrentRasterbarTargets.cmake"
	NAMESPACE LibtorrentRasterbar::
)

configure_package_config_file(LibtorrentRasterbarConfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/LibtorrentRasterbar/LibtorrentRasterbarConfig.cmake"
	INSTALL_DESTINATION "${ConfigPackageLocation}"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(EXPORT LibtorrentRasterbarTargets
	NAMESPACE
		LibtorrentRasterbar::
	DESTINATION
		${ConfigPackageLocation}
)
install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/LibtorrentRasterbar/LibtorrentRasterbarConfig.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/LibtorrentRasterbar/LibtorrentRasterbarConfigVersion.cmake"
	DESTINATION
		${ConfigPackageLocation}
)

install(
	FILES
		${CMAKE_CURRENT_SOURCE_DIR}/examples/cmake/FindLibtorrentRasterbar.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/cmake/Modules
)

if (MSVC)
	add_library(torrent-sirius ${CMAKE_CURRENT_SOURCE_DIR})
	set_target_properties(torrent-sirius
	PROPERTIES
		PDB_NAME torrent-sirius
		PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
		COMPILE_PDB_NAME torrent-sirius
		COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
		LINKER_LANGUAGE C++
	)

	if (static_runtime)
		set(PDB_INSTALL_DIR lib)
	else()
		set(PDB_INSTALL_DIR bin)
	endif()

	install(
		FILES
			${CMAKE_BINARY_DIR}/torrent-sirius.pdb
		DESTINATION
			${PDB_INSTALL_DIR}
		CONFIGURATIONS
			Debug RelWithDebInfo
		OPTIONAL
	)
endif()

# === build tools ===
if (build_tools)
	add_subdirectory(tools)
endif()

# === build examples ===
if (build_examples)
	add_subdirectory(examples)
endif()

# === build tests ===
if(build_tests)
	enable_testing()
	# this will make some internal functions available in the DLL interface
	target_compile_definitions(torrent-sirius PUBLIC TORRENT_EXPORT_EXTRA)
	add_subdirectory(test)
endif()

feature_summary(DEFAULT_DESCRIPTION WHAT ALL)