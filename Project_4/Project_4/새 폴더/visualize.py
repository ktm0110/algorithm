import sys
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import glob # 파일 패턴을 찾는 데 사용하는 모듈

def load_obstacles(filename="map.txt"):
    """
    map.txt 파일에서 장애물 정보를 읽어 리스트로 반환합니다.
    """
    try:
        with open(filename, 'r') as f:
            num_obstacles = int(f.readline())
            obstacles = [list(map(int, f.readline().split())) for _ in range(num_obstacles)]
        return obstacles
    except FileNotFoundError:
        print(f"오류: 맵 파일 '{filename}'을 찾을 수 없습니다.")
        return None

def load_path(filename):
    """
    경로 파일에서 좌표를 읽어 x, y 리스트로 반환합니다.
    """
    try:
        path_x, path_y = [], []
        with open(filename, 'r') as f:
            for line in f:
                parts = list(map(float, line.split()))
                path_x.append(parts[0])
                path_y.append(parts[1])
        return path_x, path_y
    except FileNotFoundError:
        print(f"오류: 경로 파일 '{filename}'을 찾을 수 없습니다.")
        return None, None

def visualize_all_paths():
    """
    현재 폴더의 모든 path_*.txt 파일을 찾아 하나의 그래프에 비교하여 시각화합니다.
    """
    obstacles = load_obstacles()
    if obstacles is None:
        return

    # 1. path_*.txt 패턴에 맞는 모든 파일 목록을 찾음
    path_files = sorted(glob.glob("path_*.txt"))

    if not path_files:
        print("오류: 시각화할 경로 파일(path_*.txt)을 찾을 수 없습니다.")
        print("C++ 프로그램을 먼저 실행했는지 확인하세요.")
        return

    print("다음 파일들을 시각화합니다:", path_files)

    fig, ax = plt.subplots(figsize=(12, 12))
    ax.set_title("Path Planning Algorithm Comparison", fontsize=16)

    # 2. 장애물 그리기 (한 번만)
    for obs in obstacles:
        left, top, right, bottom = obs
        rect = patches.Rectangle(
            (left - 0.5, top - 0.5), right - left + 1, bottom - top + 1,
            linewidth=1, edgecolor='black', facecolor='darkgray', zorder=2
        )
        ax.add_patch(rect)

    # 3. 각 경로 파일에 대해 반복하며 그리기
    # 각 경로에 다른 색상과 스타일을 적용하기 위한 리스트
    colors = ['dodgerblue', 'limegreen', 'red', 'purple', 'orange']
    linestyles = ['-', '--', ':', '-.']
    
    has_drawn_start_goal = False

    for i, file_path in enumerate(path_files):
        path_x, path_y = load_path(file_path)
        if not path_x:
            continue

        # 파일 이름에서 알고리즘 이름 추출
        # 예: path_A.txt -> A
        try:
            algo_name = file_path.split('_')[1].split('.')[0]
            if algo_name == 'D': label = 'Dijkstra'
            elif algo_name == 'A': label = 'A*'
            elif algo_name == 'R': label = 'RRT*'
            else: label = algo_name
        except IndexError:
            label = file_path

        # 경로 그리기
        ax.plot(path_x, path_y,
                color=colors[i % len(colors)],
                linestyle=linestyles[i % len(linestyles)],
                linewidth=2.5,
                label=f"Path ({label})",
                zorder=3 + i)

        # 시작점과 도착점은 한 번만 그리기
        if not has_drawn_start_goal:
            ax.plot(path_x[0], path_y[0], marker='o', markersize=15, color='gold', label="Start/Goal", zorder=10, mec='black')
            ax.plot(path_x[-1], path_y[-1], marker='o', markersize=15, color='gold', zorder=10, mec='black')
            has_drawn_start_goal = True
            
    # 4. 그래프 스타일 설정
    ax.set_xlabel("X coordinate")
    ax.set_ylabel("Y coordinate")
    ax.set_xticks(range(1, 21))
    ax.set_yticks(range(1, 21))
    ax.set_xlim(0.5, 20.5)
    ax.set_ylim(0.5, 20.5)
    ax.set_aspect('equal', adjustable='box')
    ax.grid(True, which='both', linestyle='--', linewidth=0.5)
    ax.legend(fontsize=12)
    
    plt.show()

if __name__ == '__main__':
    visualize_all_paths()
    input("\n시각화가 완료되었습니다. Enter 키를 누르면 종료합니다...") 
