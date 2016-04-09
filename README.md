# UDP_IM
A simple UDP IM, only run on Linux.
This is just a practice for Linux multi-threaded programming.

**The program use a 16 byte ID to identify each client, client's abortion wil make the ID never unusable.**<br />
**Server limits the number of clients to 29.**<br />
**Client supports only 4 operations: up down left right to select target client; Ctrl-C to exit normally; Enter to send message; other input will be printed on stdard output (if the character can be printed).**
**Use UDP port 8888.**

Depend on
---
**ncurses** get from: http://www.gnu.org/order/ftp.html。
