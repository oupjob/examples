import telnetlib

host = 'localhost'
user = 'r2d2'
passwd = 'multiC'


tn = telnetlib.Telnet(host)

print(tn.read_until(b"login"))
tn.write(user.encode('ascii') + b"\n")

print(tn.read_until(b"Password"))
tn.write(passwd.encode('ascii') + b"\n")

print(tn.read_until(b'mail.'))

i = 0xF9 # 0xF1, ..., 0xF9
for i in range(0xF1, 0xFA):
    tn.msg("send %r", bytes([0xFF, i]))
    tn.sock.sendall(bytes([0xFF, i]))
    print(tn.read_until(b''))

