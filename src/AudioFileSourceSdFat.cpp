/*
  AudioFileSourceSPIFFS
  Input SD card "file" to be used by AudioGenerator
  Adapted for SdFat
  
  Copyright (C) 2017  Earle F. Philhower, III

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "AudioFileSourceSdFat.h"

AudioFileSourceSdFat::AudioFileSourceSdFat() : f(SdFile())
{
}

AudioFileSourceSdFat::AudioFileSourceSdFat(const char *filename)
{
  open(filename);
}

bool AudioFileSourceSdFat::open(const char *filename)
{
  close();
  f.open(filename, FILE_READ);
  return f;
}

AudioFileSourceSdFat::~AudioFileSourceSdFat()
{
  if (f) f.close();
}

uint32_t AudioFileSourceSdFat::read(void *data, uint32_t len)
{
  return f.read(reinterpret_cast<uint8_t*>(data), len);
}

bool AudioFileSourceSdFat::seek(int32_t pos, int dir)
{
  if (!f) return false;
  if (dir==SEEK_SET) return  f.seekSet(pos);
  else if (dir==SEEK_CUR) return f.seekSet(f.curPosition() + pos);
  else if (dir==SEEK_END) return f.seekSet(f.fileSize() + pos);
  return false;
}

bool AudioFileSourceSdFat::close()
{
  f.close();
  return true;
}

bool AudioFileSourceSdFat::isOpen()
{
  return f.isOpen();
}

uint32_t AudioFileSourceSdFat::getSize()
{
  if (!f) return 0;
  return f.fileSize();
}

uint32_t AudioFileSourceSdFat::getPos()
{
  if (!f) return 0;
  return f.curPosition();
}
