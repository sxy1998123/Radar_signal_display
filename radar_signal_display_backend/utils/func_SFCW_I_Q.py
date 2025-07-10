import numpy as np
import matplotlib.pyplot as plt
from typing import Tuple, Optional
import logging
def generate_step_freq_signal(
    fs: float = 3e9,          # 采样率 (Hz)
    fc_start: float = 300e6,  # 起始频率 (Hz)
    fc_end: float = 1000e6,   # 结束频率 (Hz)
    T: float = 50e-8,         # 单个频率持续时间 (s)
    use_iq: bool = True,      # 是否生成IQ信号,true为同时生成I相和Q相信号，Flase为只生成I相信号
    num_steps: int = 101      # 步进频率点数
) -> Tuple[np.ndarray, Optional[np.ndarray]]:
    """
    生成步进频信号
    
    参数:
        fs: 采样率 (Hz)
        fc_start: 起始频率 (Hz)
        fc_end: 结束频率 (Hz)
        T: 单个频率持续时间 (s)
        use_iq: 是否生成IQ信号
        num_steps: 步进频率点数
    
    返回:
        (i_signal, q_signal) 元组，如果use_iq=False，q_signal为None
    """
    # 计算时间向量
    t = np.arange(0, T, 1/fs)
    samples_per_step = len(t)
    
    # 信号参数 (固定)
    bit_depth = 16
    amplitude = (2**(bit_depth-1) - 100)
    offset = 0
    
    # 生成频率列表
    freq_list = np.linspace(fc_start, fc_end, num_steps)
    
    # 初始化信号存储
    i_signal = np.zeros(samples_per_step * num_steps, dtype=np.int16)
    q_signal = np.zeros_like(i_signal) if use_iq else None
    
    # 生成信号
    for i, freq in enumerate(freq_list):
        start = i * samples_per_step
        end = (i + 1) * samples_per_step
        
        # I信号
        i_wave = amplitude * np.cos(2 * np.pi * freq * t)
        i_signal[start:end] = np.round(i_wave + offset).astype(np.int16)
        
        # Q信号
        if use_iq:
            q_wave = -amplitude * np.sin(2 * np.pi * freq * t)
            q_signal[start:end] = np.round(q_wave + offset).astype(np.int16)
    
    return i_signal, q_signal

def plot_time_domain(
    signal: np.ndarray,
    signal_type: str = "I",
    show: bool = True
) -> plt.Figure:
    """
    绘制时域信号
    
    参数:
        signal: 输入信号
        signal_type: 信号类型 ("I"或"Q")
        show: 是否立即显示图形
    
    返回:
        matplotlib Figure对象
    """
    fig = plt.figure(figsize=(12, 4))
    plt.plot(signal)
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.title(f'{signal_type}Stepped Frequency Signal')
    plt.grid(True)
    
    if show:
        plt.show()
    
    return fig

def plot_frequency_domain(
    signal: np.ndarray,
    fs: float,
    signal_type: str = "I",
    show: bool = True
) -> plt.Figure:
    """
    绘制频域信号
    
    参数:
        signal: 输入信号
        fs: 采样率
        signal_type: 信号类型 ("I"或"Q")
        show: 是否立即显示图形
    
    返回:
        matplotlib Figure对象
    """
    N = len(signal)
    fft_result = np.fft.fft(signal)
    fft_mag = 20 * np.log10(np.abs(fft_result)[:N//2])
    freqs = np.fft.fftfreq(N, 1/fs)[:N//2] / 1e6  # MHz
    
    fig = plt.figure(figsize=(12, 4))
    plt.plot(freqs, fft_mag)
    plt.xlabel('Frequency (MHz)')
    plt.ylabel('Magnitude (dB)')
    plt.title(f'{signal_type}Frequency Spectrum')
    plt.xlim([0, fs/2/1e6])
    plt.grid(True)
    
    if show:
        plt.show()
    
    return fig

def save_signal_with_prompt(signal: np.ndarray, signal_type: str = "I") -> Optional[str]:
    """
    带提示保存信号到二进制文件
    
    参数:
        signal: 输入信号
        signal_type: 信号类型 ("I"或"Q")
    
    返回:
        保存的文件名（如果成功），否则返回None
    """
    while True:
        try:
            filename = input(f"请输入{signal_type}相信号保存文件名(不含扩展名): ").strip()
            if not filename:
                print("文件名不能为空，请重新输入")
                continue
                
            if not filename.endswith('.bin'):
                filename += '.bin'
            
            with open(filename, 'wb') as f:
                f.write(signal.tobytes())
            
            print(f"{signal_type}相信号已成功保存到 {filename}")
            return filename
            
        except KeyboardInterrupt:
            print("\n用户取消保存操作")
            return None
        except Exception as e:
            print(f"保存失败: {e}")
            retry = input("是否重试? (y/n): ").lower()
            if retry != 'y':
                return None

def save_signal_with_dir(signal: np.ndarray, signal_type: str = "I", save_dir: str = "") -> Optional[str]:
    """
    保存信号到二进制文件，不带提示
    
    参数:
        signal: 输入信号
        signal_type: 信号类型 ("I"或"Q")
        save_dir: 保存目录
    
    返回:
        保存的文件名（如果成功），否则返回None
    """
    if not save_dir:
        loggin.error("保存目录不能为空")
        return None
    try:
        filename = f"{save_dir}/{signal_type}_signal.bin"
        
        with open(filename, 'wb') as f:
            f.write(signal.tobytes())
        
        print(f"{signal_type}相信号已成功保存到 {save_dir}")
        return filename
        
    except KeyboardInterrupt:
        print("\n用户取消保存操作")
        return None
    except Exception as e:
        print(f"保存失败: {e}")
        return None


# 使用示例
# if __name__ == "__main__":
#     # 1. 生成信号
#     i_sig, q_sig = generate_step_freq_signal(
#         fs=3e9,         # 采样率 (Hz)
#         fc_start=300e6, # 起始频率 (Hz)
#         fc_end=1000e6,  # 结束频率 (Hz)
#         T=50e-8,        # 单个频率持续时间 (s)
#         use_iq=True,    # 是否生成IQ信号,true为同时生成I相和Q相信号，Flase为只生成I相信号
#         num_steps=101   # 步进频率点数
#     )
    
#     # 2. 绘制信号
#     plot_time_domain(i_sig, "I_")
#     plot_frequency_domain(i_sig, fs=3e9, signal_type="I_")
    
#     if q_sig is not None:
#         plot_time_domain(q_sig, "Q_")
#         plot_frequency_domain(q_sig, fs=3e9, signal_type="Q_")
    
#     # 3. 保存信号（带自定义命名）
#     print("\n保存I相信号:")
#     saved_i_file = save_signal_with_prompt(i_sig, "I")
    
#     if q_sig is not None:
#         print("\n保存Q相信号:")
#         saved_q_file = save_signal_with_prompt(q_sig, "Q")