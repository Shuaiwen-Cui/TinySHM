import pywt

def format_c_array(array, name):
    c_code = f"const float {name}[{len(array)}] = {{\n"
    for i, val in enumerate(array):
        formatted_val = f"{val:.8f}f"
        if i != len(array) - 1:
            formatted_val += ","
        c_code += f"  {formatted_val}"
        if (i + 1) % 4 == 0 or i == len(array) - 1:
            c_code += "\n"
    c_code += "};\n"
    return c_code

def export_wavelet(wavelet_name):
    try:
        wavelet = pywt.Wavelet(wavelet_name)

        safe_name = wavelet_name.lower().replace('-', '_').replace('.', '_')

        lo_d = wavelet.dec_lo
        hi_d = wavelet.dec_hi
        lo_r = wavelet.rec_lo
        hi_r = wavelet.rec_hi

        print(f"// {wavelet_name} wavelet filters\n")

        print(format_c_array(lo_d, f"{safe_name}_lo_d"))  # decomposition low-pass
        print(format_c_array(hi_d, f"{safe_name}_hi_d"))  # decomposition high-pass
        print(format_c_array(lo_r, f"{safe_name}_lo_r"))  # reconstruction low-pass
        print(format_c_array(hi_r, f"{safe_name}_hi_r"))  # reconstruction high-pass

    except Exception as e:
        print(f"Error: Failed to export wavelet '{wavelet_name}' - {e}")

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python export_wavelet_to_c.py <wavelet_name>")
        print("Example: python export_wavelet_to_c.py db4")
    else:
        export_wavelet(sys.argv[1])
