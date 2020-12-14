;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                          ;;
;;  SeaTCP - Low latency TCP/IP stack                                       ;;
;;  Copyright (C) 2020  Sebastian Majewski                                  ;;
;;                                                                          ;;
;;  This program is free software: you can redistribute it and/or modify    ;;
;;  it under the terms of the GNU General Public License as published by    ;;
;;  the Free Software Foundation, either version 3 of the License, or       ;;
;;  (at your option) any later version.                                     ;;
;;                                                                          ;;
;;  This program is distributed in the hope that it will be useful,         ;;
;;  but WITHOUT ANY WARRANTY; without even the implied warranty of          ;;
;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           ;;
;;  GNU General Public License for more details.                            ;;
;;                                                                          ;;
;;  You should have received a copy of the GNU General Public License       ;;
;;  along with this program.  If not, see <https://www.gnu.org/licenses/>.  ;;
;;                                                                          ;;
;;  Author's email: ccie18643@gmail.com                                     ;;
;;  Github repository: https://github.com/ccie18643/SeaTCP                  ;;
;;                                                                          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
; Arguments passed from C 
;
; rdi - pointer to data block
; rsi - length of data block
; rdx - version of optional IP header for pseudo header computation
; rcx - pointer to optional IP header for pseudo header computation
; r8  - overide 16-bit IPv6 payload length field with 32-bit value for fragmented packets
;
;
; Computed checksum value to be stored in rax register
;

                global  inet_cksum
                section .text

inet_cksum:
                xor rax, rax
                cmp rdx, 4                  ; IPv4 pseudo header checksum computation requested
                je phdr_v4
                cmp rdx, 6                  ; IPv6 pseudo header checksum computation requested
                je phdr_v6
                jmp cksum_data              ; no pseudo header checksum computation requested

phdr_v4:
                xor rcx, rcx
                mov cx, [rdx + 0x02]        ; packet length
                add rax, rcx
                xor rcx, rcx
                mov cl, [rdx + 0x09]        ; protocol
                add rax, rcx
                xor rcx, rcx
                mov ecx, [rdx + 0x0C]       ; source address
                add rax, rcx
                xor rcx, rcx
                mov ecx, [rdx + 0x0C]       ; destination address
                add rax, rcx
                jmp cksum_data

phdr_v6:
                xor rcx, rcx
                mov cx, [rdx + 0x04]        ; payload length
                cmp r8, 0                   ; overide payload field value if 32-bit value available in r8 register
                je no_pl_overide
                mov rcx, r8

no_pl_overide: 
                add rax, rcx
                xor rcx, rcx
                mov cl, [rdx + 0x06]        ; next header
                add rax, rcx
                add rax, [rdx + 0x08]       ; source address
                adc rax, [rdx + 0x10]       ; source address
                adc rax, [rdx + 0x18]       ; destination address
                adc rax, [rdx + 0x20]       ; destination address
                adc rax, 0

cksum_data:
                cmp rsi, 1024
                jl bytes_512

bytes_1024:
                add rax, [rdi + 8 * 0x00]
                adc rax, [rdi + 8 * 0x01]
                adc rax, [rdi + 8 * 0x02]
                adc rax, [rdi + 8 * 0x03]
                adc rax, [rdi + 8 * 0x04]
                adc rax, [rdi + 8 * 0x05]
                adc rax, [rdi + 8 * 0x06]
                adc rax, [rdi + 8 * 0x07]
                adc rax, [rdi + 8 * 0x08]
                adc rax, [rdi + 8 * 0x09]
                adc rax, [rdi + 8 * 0x0A]
                adc rax, [rdi + 8 * 0x0B]
                adc rax, [rdi + 8 * 0x0C]
                adc rax, [rdi + 8 * 0x0D]
                adc rax, [rdi + 8 * 0x0E]
                adc rax, [rdi + 8 * 0x0F]
                adc rax, [rdi + 8 * 0x10]
                adc rax, [rdi + 8 * 0x11]
                adc rax, [rdi + 8 * 0x12]
                adc rax, [rdi + 8 * 0x13]
                adc rax, [rdi + 8 * 0x14]
                adc rax, [rdi + 8 * 0x15]
                adc rax, [rdi + 8 * 0x16]
                adc rax, [rdi + 8 * 0x17]
                adc rax, [rdi + 8 * 0x18]
                adc rax, [rdi + 8 * 0x19]
                adc rax, [rdi + 8 * 0x1A]
                adc rax, [rdi + 8 * 0x1B]
                adc rax, [rdi + 8 * 0x1C]
                adc rax, [rdi + 8 * 0x1D]
                adc rax, [rdi + 8 * 0x1E]
                adc rax, [rdi + 8 * 0x1F]
                adc rax, [rdi + 8 * 0x20]
                adc rax, [rdi + 8 * 0x21]
                adc rax, [rdi + 8 * 0x22]
                adc rax, [rdi + 8 * 0x23]
                adc rax, [rdi + 8 * 0x24]
                adc rax, [rdi + 8 * 0x25]
                adc rax, [rdi + 8 * 0x26]
                adc rax, [rdi + 8 * 0x27]
                adc rax, [rdi + 8 * 0x28]
                adc rax, [rdi + 8 * 0x29]
                adc rax, [rdi + 8 * 0x2A]
                adc rax, [rdi + 8 * 0x2B]
                adc rax, [rdi + 8 * 0x2C]
                adc rax, [rdi + 8 * 0x2D]
                adc rax, [rdi + 8 * 0x2E]
                adc rax, [rdi + 8 * 0x2F]
                adc rax, [rdi + 8 * 0x30]
                adc rax, [rdi + 8 * 0x31]
                adc rax, [rdi + 8 * 0x32]
                adc rax, [rdi + 8 * 0x33]
                adc rax, [rdi + 8 * 0x34]
                adc rax, [rdi + 8 * 0x35]
                adc rax, [rdi + 8 * 0x36]
                adc rax, [rdi + 8 * 0x37]
                adc rax, [rdi + 8 * 0x38]
                adc rax, [rdi + 8 * 0x39]
                adc rax, [rdi + 8 * 0x3A]
                adc rax, [rdi + 8 * 0x3B]
                adc rax, [rdi + 8 * 0x3C]
                adc rax, [rdi + 8 * 0x3D]
                adc rax, [rdi + 8 * 0x3E]
                adc rax, [rdi + 8 * 0x3F]
                adc rax, [rdi + 8 * 0x40]
                adc rax, [rdi + 8 * 0x41]
                adc rax, [rdi + 8 * 0x42]
                adc rax, [rdi + 8 * 0x43]
                adc rax, [rdi + 8 * 0x44]
                adc rax, [rdi + 8 * 0x45]
                adc rax, [rdi + 8 * 0x46]
                adc rax, [rdi + 8 * 0x47]
                adc rax, [rdi + 8 * 0x48]
                adc rax, [rdi + 8 * 0x49]
                adc rax, [rdi + 8 * 0x4A]
                adc rax, [rdi + 8 * 0x4B]
                adc rax, [rdi + 8 * 0x4C]
                adc rax, [rdi + 8 * 0x4D]
                adc rax, [rdi + 8 * 0x4E]
                adc rax, [rdi + 8 * 0x4F]
                adc rax, [rdi + 8 * 0x50]
                adc rax, [rdi + 8 * 0x51]
                adc rax, [rdi + 8 * 0x52]
                adc rax, [rdi + 8 * 0x53]
                adc rax, [rdi + 8 * 0x54]
                adc rax, [rdi + 8 * 0x55]
                adc rax, [rdi + 8 * 0x56]
                adc rax, [rdi + 8 * 0x57]
                adc rax, [rdi + 8 * 0x58]
                adc rax, [rdi + 8 * 0x59]
                adc rax, [rdi + 8 * 0x5A]
                adc rax, [rdi + 8 * 0x5B]
                adc rax, [rdi + 8 * 0x5C]
                adc rax, [rdi + 8 * 0x5D]
                adc rax, [rdi + 8 * 0x5E]
                adc rax, [rdi + 8 * 0x5F]
                adc rax, [rdi + 8 * 0x60]
                adc rax, [rdi + 8 * 0x61]
                adc rax, [rdi + 8 * 0x62]
                adc rax, [rdi + 8 * 0x63]
                adc rax, [rdi + 8 * 0x64]
                adc rax, [rdi + 8 * 0x65]
                adc rax, [rdi + 8 * 0x66]
                adc rax, [rdi + 8 * 0x67]
                adc rax, [rdi + 8 * 0x68]
                adc rax, [rdi + 8 * 0x69]
                adc rax, [rdi + 8 * 0x6A]
                adc rax, [rdi + 8 * 0x6B]
                adc rax, [rdi + 8 * 0x6C]
                adc rax, [rdi + 8 * 0x6D]
                adc rax, [rdi + 8 * 0x6E]
                adc rax, [rdi + 8 * 0x6F]
                adc rax, [rdi + 8 * 0x70]
                adc rax, [rdi + 8 * 0x71]
                adc rax, [rdi + 8 * 0x72]
                adc rax, [rdi + 8 * 0x73]
                adc rax, [rdi + 8 * 0x74]
                adc rax, [rdi + 8 * 0x75]
                adc rax, [rdi + 8 * 0x76]
                adc rax, [rdi + 8 * 0x77]
                adc rax, [rdi + 8 * 0x78]
                adc rax, [rdi + 8 * 0x79]
                adc rax, [rdi + 8 * 0x7A]
                adc rax, [rdi + 8 * 0x7B]
                adc rax, [rdi + 8 * 0x7C]
                adc rax, [rdi + 8 * 0x7D]
                adc rax, [rdi + 8 * 0x7E]
                adc rax, [rdi + 8 * 0x7F]
                adc rax, 0
                add rdi, 1024
                sub rsi, 1024
                cmp rsi, 1024
                jge bytes_1024

bytes_512:
                cmp rsi, 512
                jl bytes_256
                add rax, [rdi + 8 * 0x00]
                adc rax, [rdi + 8 * 0x01]
                adc rax, [rdi + 8 * 0x02]
                adc rax, [rdi + 8 * 0x03]
                adc rax, [rdi + 8 * 0x04]
                adc rax, [rdi + 8 * 0x05]
                adc rax, [rdi + 8 * 0x06]
                adc rax, [rdi + 8 * 0x07]
                adc rax, [rdi + 8 * 0x08]
                adc rax, [rdi + 8 * 0x09]
                adc rax, [rdi + 8 * 0x0A]
                adc rax, [rdi + 8 * 0x0B]
                adc rax, [rdi + 8 * 0x0C]
                adc rax, [rdi + 8 * 0x0D]
                adc rax, [rdi + 8 * 0x0E]
                adc rax, [rdi + 8 * 0x0F]
                adc rax, [rdi + 8 * 0x10]
                adc rax, [rdi + 8 * 0x11]
                adc rax, [rdi + 8 * 0x12]
                adc rax, [rdi + 8 * 0x13]
                adc rax, [rdi + 8 * 0x14]
                adc rax, [rdi + 8 * 0x15]
                adc rax, [rdi + 8 * 0x16]
                adc rax, [rdi + 8 * 0x17]
                adc rax, [rdi + 8 * 0x18]
                adc rax, [rdi + 8 * 0x19]
                adc rax, [rdi + 8 * 0x1A]
                adc rax, [rdi + 8 * 0x1B]
                adc rax, [rdi + 8 * 0x1C]
                adc rax, [rdi + 8 * 0x1D]
                adc rax, [rdi + 8 * 0x1E]
                adc rax, [rdi + 8 * 0x1F]
                adc rax, [rdi + 8 * 0x20]
                adc rax, [rdi + 8 * 0x21]
                adc rax, [rdi + 8 * 0x22]
                adc rax, [rdi + 8 * 0x23]
                adc rax, [rdi + 8 * 0x24]
                adc rax, [rdi + 8 * 0x25]
                adc rax, [rdi + 8 * 0x26]
                adc rax, [rdi + 8 * 0x27]
                adc rax, [rdi + 8 * 0x28]
                adc rax, [rdi + 8 * 0x29]
                adc rax, [rdi + 8 * 0x2A]
                adc rax, [rdi + 8 * 0x2B]
                adc rax, [rdi + 8 * 0x2C]
                adc rax, [rdi + 8 * 0x2D]
                adc rax, [rdi + 8 * 0x2E]
                adc rax, [rdi + 8 * 0x2F]
                adc rax, [rdi + 8 * 0x30]
                adc rax, [rdi + 8 * 0x31]
                adc rax, [rdi + 8 * 0x32]
                adc rax, [rdi + 8 * 0x33]
                adc rax, [rdi + 8 * 0x34]
                adc rax, [rdi + 8 * 0x35]
                adc rax, [rdi + 8 * 0x36]
                adc rax, [rdi + 8 * 0x37]
                adc rax, [rdi + 8 * 0x38]
                adc rax, [rdi + 8 * 0x39]
                adc rax, [rdi + 8 * 0x3A]
                adc rax, [rdi + 8 * 0x3B]
                adc rax, [rdi + 8 * 0x3C]
                adc rax, [rdi + 8 * 0x3D]
                adc rax, [rdi + 8 * 0x3E]
                adc rax, [rdi + 8 * 0x3F]
                adc rax, 0
                add rdi, 512
                sub rsi, 512

bytes_256:
                cmp rsi, 256
                jl bytes_128
                add rax, [rdi + 8 * 0x00]
                adc rax, [rdi + 8 * 0x01]
                adc rax, [rdi + 8 * 0x02]
                adc rax, [rdi + 8 * 0x03]
                adc rax, [rdi + 8 * 0x04]
                adc rax, [rdi + 8 * 0x05]
                adc rax, [rdi + 8 * 0x06]
                adc rax, [rdi + 8 * 0x07]
                adc rax, [rdi + 8 * 0x08]
                adc rax, [rdi + 8 * 0x09]
                adc rax, [rdi + 8 * 0x0A]
                adc rax, [rdi + 8 * 0x0B]
                adc rax, [rdi + 8 * 0x0C]
                adc rax, [rdi + 8 * 0x0D]
                adc rax, [rdi + 8 * 0x0E]
                adc rax, [rdi + 8 * 0x0F]
                adc rax, [rdi + 8 * 0x10]
                adc rax, [rdi + 8 * 0x11]
                adc rax, [rdi + 8 * 0x12]
                adc rax, [rdi + 8 * 0x13]
                adc rax, [rdi + 8 * 0x14]
                adc rax, [rdi + 8 * 0x15]
                adc rax, [rdi + 8 * 0x16]
                adc rax, [rdi + 8 * 0x17]
                adc rax, [rdi + 8 * 0x18]
                adc rax, [rdi + 8 * 0x19]
                adc rax, [rdi + 8 * 0x1A]
                adc rax, [rdi + 8 * 0x1B]
                adc rax, [rdi + 8 * 0x1C]
                adc rax, [rdi + 8 * 0x1D]
                adc rax, [rdi + 8 * 0x1E]
                adc rax, [rdi + 8 * 0x1F]
                adc rax, 0
                add rdi, 256
                sub rsi, 256

bytes_128:
                cmp rsi, 128 
                jl bytes_64
                add rax, [rdi + 8 * 0x00]
                adc rax, [rdi + 8 * 0x01]
                adc rax, [rdi + 8 * 0x02]
                adc rax, [rdi + 8 * 0x03]
                adc rax, [rdi + 8 * 0x04]
                adc rax, [rdi + 8 * 0x05]
                adc rax, [rdi + 8 * 0x06]
                adc rax, [rdi + 8 * 0x07]
                adc rax, [rdi + 8 * 0x08]
                adc rax, [rdi + 8 * 0x09]
                adc rax, [rdi + 8 * 0x0A]
                adc rax, [rdi + 8 * 0x0B]
                adc rax, [rdi + 8 * 0x0C]
                adc rax, [rdi + 8 * 0x0D]
                adc rax, [rdi + 8 * 0x0E]
                adc rax, [rdi + 8 * 0x0F]
                adc rax, 0
                add rdi, 128
                sub rsi, 128

bytes_64:
                cmp rsi, 64 
                jl bytes_32
                add rax, [rdi + 8 * 0x00]
                adc rax, [rdi + 8 * 0x01]
                adc rax, [rdi + 8 * 0x02]
                adc rax, [rdi + 8 * 0x03]
                adc rax, [rdi + 8 * 0x04]
                adc rax, [rdi + 8 * 0x05]
                adc rax, [rdi + 8 * 0x06]
                adc rax, [rdi + 8 * 0x07]
                adc rax, 0
                add rdi, 64
                sub rsi, 64

bytes_32:
                cmp rsi, 32
                jl bytes_16
                add rax, [rdi + 8 * 0x00]
                adc rax, [rdi + 8 * 0x01]
                adc rax, [rdi + 8 * 0x02]
                adc rax, [rdi + 8 * 0x03]
                adc rax, 0
                add rdi, 32
                sub rsi, 32

bytes_16:
                cmp rsi, 16
                jl bytes_8
                add rax, [rdi + 8 * 0x00]
                adc rax, [rdi + 8 * 0x01]
                adc rax, 0
                add rdi, 16
                sub rsi, 16
bytes_8:
                cmp rsi, 8
                jl bytes_4
                add rax, [rdi + 8 * 0x00]
                adc rax, 0
                add rdi, 8
                sub rsi, 8

bytes_4:
                cmp rsi, 4
                jl bytes_2
                xor rcx, rcx
                mov ecx, [rdi]
                add rax, rcx
                adc rax, 0
                add rdi, 4
                sub rsi, 4

bytes_2:
                cmp rsi, 2
                jl bytes_1
                xor rcx, rcx
                mov cx, [rdi]
                add rax, rcx
                adc rax, 0
                add rdi, 2
                sub rsi, 2

bytes_1:
                cmp rsi, 1
                jl fold
                xor rcx, rcx
                mov cl, [rdi]
                add rax, rcx
                adc rax, 0

fold:
                mov rcx, rax
                shr rcx, 32
                and rax, 0xffffffff
                add eax, ecx
                adc eax, 0
                mov ecx, eax
                shr ecx, 16
                and eax, 0xffff
                add ax, cx
                adc ax, 0

                not rax
                and rax, 0xffff

                ret
