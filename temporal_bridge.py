import ctypes
import os
import sys

class TemporalBridge:
    def __init__(self):
        if not os.path.exists("./libtemporal.so") and not os.path.exists("./libtemporal.dll"):
            if sys.platform.startswith("win"):
                os.system("gcc -shared -o libtemporal.dll temporal_btree.c")
                lib_path = "./libtemporal.dll"
            else:
                os.system("gcc -shared -fPIC -o libtemporal.so temporal_btree.c")
                lib_path = "./libtemporal.so"
        else:
            lib_path = "./libtemporal.dll" if sys.platform.startswith("win") else "./libtemporal.so"

        self.lib = ctypes.CDLL(lib_path)
        self.lib.init_btree_node.restype = ctypes.c_void_p
        self.lib.insert_temporal_key.argtypes = [ctypes.c_void_p, ctypes.c_longlong, ctypes.c_int]
        self.lib.scan_time_window.argtypes = [ctypes.c_void_p, ctypes.c_longlong]
        self.lib.scan_time_window.restype = ctypes.c_int
        
        self.root_ptr = self.lib.init_btree_node()

    def add_historical_record(self, epoch_time: int, chunk_id: int):
        self.lib.insert_temporal_key(self.root_ptr, epoch_time, chunk_id)

    def locate_epoch_match(self, epoch_time: int) -> int:
        return self.lib.scan_time_window(self.root_ptr, epoch_time)
