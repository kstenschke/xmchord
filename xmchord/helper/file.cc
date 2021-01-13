/*
  Copyright (c) Kay Stenschke
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of  nor the names of its contributors may be used to
     endorse or promote products derived from this software without specific
     prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include <xmchord/helper/file.h>

namespace helper {

bool File::FileExists(const std::string &name) {
  return access(name.c_str(), F_OK) != -1;
}

std::string File::GetLastPathSegment(std::string path) {
  if (path.find('/') == std::string::npos) return path;

  std::vector<std::string> parts = helper::Textual::Explode(path, '/');

  return parts[parts.size() - 1];
}

uint8_t File::GeLongestFilenameLength(DIR *dir_stream) {
  uint8_t len_longest = 0;
  uint8_t len_filename;
  struct dirent *ent;

  while ((ent = readdir(dir_stream)) != nullptr) {
    if (ent->d_name[0] == '.'
        || !helper::Textual::EndsWith(ent->d_name, ".sh")) continue;

    len_filename = strlen(ent->d_name);

    if (len_filename > len_longest) len_longest = len_filename;
  }

  rewinddir(dir_stream);

  return len_longest;
}

std::string File::GetFileContents(const std::string &filename) {
  std::ifstream file(filename);

  return GetFileContents(file);
}

std::string File::GetFileContents(std::ifstream &file) {
  // Get file size
  file.seekg(0, std::ios::end);
  std::streampos length = file.tellg();
  file.seekg(0, std::ios::beg);

  // Read the whole file into the buffer
  std::vector<char> buffer(static_cast<uint64_t>(length));
  file.read(&buffer[0], length);

  std::string str(buffer.begin(), buffer.end());

  return str;
}

bool File::OverwriteFile(const std::string &filename,
                         const std::string &content) {
  std::ofstream out_file(filename, std::ofstream::trunc);
  out_file << content;
  out_file.close();

  return File::FileExists(filename);
}

}  // namespace helper
