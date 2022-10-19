// Copyright (c) 2022 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
// $hash=5e121ff2140e0f1228fd8e2ad632c804ab854210$
//

#ifndef CEF_INCLUDE_CAPI_CEF_ZIP_READER_CAPI_H_
#define CEF_INCLUDE_CAPI_CEF_ZIP_READER_CAPI_H_
#pragma once

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_stream_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

///
/// Structure that supports the reading of zip archives via the zlib unzip API.
/// The functions of this structure should only be called on the thread that
/// creates the object.
///
typedef struct _cef_zip_reader_t {
  ///
  /// Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  /// Moves the cursor to the first file in the archive. Returns true (1) if the
  /// cursor position was set successfully.
  ///
  int(CEF_CALLBACK* move_to_first_file)(struct _cef_zip_reader_t* self);

  ///
  /// Moves the cursor to the next file in the archive. Returns true (1) if the
  /// cursor position was set successfully.
  ///
  int(CEF_CALLBACK* move_to_next_file)(struct _cef_zip_reader_t* self);

  ///
  /// Moves the cursor to the specified file in the archive. If |caseSensitive|
  /// is true (1) then the search will be case sensitive. Returns true (1) if
  /// the cursor position was set successfully.
  ///
  int(CEF_CALLBACK* move_to_file)(struct _cef_zip_reader_t* self,
                                  const cef_string_t* fileName,
                                  int caseSensitive);

  ///
  /// Closes the archive. This should be called directly to ensure that cleanup
  /// occurs on the correct thread.
  ///
  int(CEF_CALLBACK* close)(struct _cef_zip_reader_t* self);

  ///
  /// Returns the name of the file.
  ///
  // The resulting string must be freed by calling cef_string_userfree_free().
  cef_string_userfree_t(CEF_CALLBACK* get_file_name)(
      struct _cef_zip_reader_t* self);

  ///
  /// Returns the uncompressed size of the file.
  ///
  int64(CEF_CALLBACK* get_file_size)(struct _cef_zip_reader_t* self);

  ///
  /// Returns the last modified timestamp for the file.
  ///
  cef_basetime_t(CEF_CALLBACK* get_file_last_modified)(
      struct _cef_zip_reader_t* self);

  ///
  /// Opens the file for reading of uncompressed data. A read password may
  /// optionally be specified.
  ///
  int(CEF_CALLBACK* open_file)(struct _cef_zip_reader_t* self,
                               const cef_string_t* password);

  ///
  /// Closes the file.
  ///
  int(CEF_CALLBACK* close_file)(struct _cef_zip_reader_t* self);

  ///
  /// Read uncompressed file contents into the specified buffer. Returns < 0 if
  /// an error occurred, 0 if at the end of file, or the number of bytes read.
  ///
  int(CEF_CALLBACK* read_file)(struct _cef_zip_reader_t* self,
                               void* buffer,
                               size_t bufferSize);

  ///
  /// Returns the current offset in the uncompressed file contents.
  ///
  int64(CEF_CALLBACK* tell)(struct _cef_zip_reader_t* self);

  ///
  /// Returns true (1) if at end of the file contents.
  ///
  int(CEF_CALLBACK* eof)(struct _cef_zip_reader_t* self);
} cef_zip_reader_t;

///
/// Create a new cef_zip_reader_t object. The returned object's functions can
/// only be called from the thread that created the object.
///
CEF_EXPORT cef_zip_reader_t* cef_zip_reader_create(
    struct _cef_stream_reader_t* stream);

#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_CEF_ZIP_READER_CAPI_H_
