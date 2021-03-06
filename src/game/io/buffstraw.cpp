/**
 * @file
 *
 * @author CCHyper
 * @author OmniBlade
 *
 * @brief Straw stream class implementation reading data from a memory buffer.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "buffstraw.h"
#include "minmax.h"
#include <string.h>

/**
* @brief Reads data to the provided buffer from the underlying buffer class.
*/
int BufferStraw::Get(void *buffer, int length)
{
    if (!m_buffer.Get_Buffer() || !buffer || length <= 0) {
        return 0;
    }

    int read_len = m_buffer.Get_Size();

    if (read_len) {
        read_len -= m_index;
        read_len = Min(length, read_len);
    }

    if (read_len > 0) {
        memmove(buffer, m_buffer.Get_Buffer() + m_index, read_len);
    }

    m_index += read_len;

    return read_len;
}
