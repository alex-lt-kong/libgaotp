import ctypes as ct
import os

so_file_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../build/src/libgaotp.so')


gaotp = ct.CDLL(so_file_path)

gaotp.get_otp.argtypes = [ct.c_char_p, ct.c_int]
gaotp.get_otp.restype =  ct.c_int

b32_secret = ct.create_string_buffer(b'JBSWY3DPEB3W64TMMQQQ====') # base32("Hello world!")

otp = gaotp.get_otp(b32_secret, ct.c_int(-1))
print(otp)