# Animation Tutorial Game

이 프로젝트는 raylib 라이브러리를 사용하여 2D 게임을 만드는 방법을 배울 수 있는 간단한 예제입니다.

이 게임은 raylib 라이브러리를 사용하여 구현되었습니다.

더 많은 정보를 원하시면 [raylib](https://www.raylib.com/) 공식 문서를 참고하세요.

<div align="center">
  
  <img width="300" src="https://github.com/user-attachments/assets/b2fb20af-0b40-436c-82d9-259839c99bcb">

  [Click here to try](https://d2t6lweoml4q5z.cloudfront.net/game/3)
  
</div>

## 설명
c 언어를 게임으로 배우기 위해 만든 프로젝트 입니다.

저 자신도 주니어 개발자라 이번 프로젝트를 통해 많이 배웠습니다.

코드를 누구나 더 쉽게 사용하기 위해 호출할 함수의 범위를 제한해야 한다는 생각이 들었습니다.

더 쉽게 많들기 위해 c++로 확장을 예정하고 있습니다.

## 빌드
raylib이 필요합니다. 

작성된 `CMakeLists.txt`파일은 homebrew를 통해 raylib을 설치했을 경우에만 빌드됩니다.

cmake에 익숙하시면 raylib 설치경로를 `CMakeLists.txt`에서 변경해 주세요

### homewrew로 raylib 설치

```
brew install raylib
```

## 파일 구조
- src 폴더 내의 파일은 클래스 처럼 작성한다.
- 파일은 하나의 구조체를 가진다.
- 파일 내부의 함수는 구조체의 맴버변수를 수정한다.
- 파일 외부의 구조체에 대해서는 call by value 만 허용한다.
- 게임은 main.c 에서 실행한다.

## 주요 파일
- ### main.c
  main.c 파일은 게임의 초기화, 메인 루프, 그리고 종료 절차를 포함하고 있습니다.

- ### env_item.c

  게임 내의 환경 아이템을 정의하고 관리하는 함수들을 포함하고 있습니다.

  맵에 그리거나 그리지 않아도 되는 벽 입니다.

  - #### 주요 함수
     - `EnvItem createEnvItem(...)`: 새로운 환경 아이템을 생성하고 초기화합니다.
     
- ### player.c
  파일은 플레이어 캐릭터를 생성하고 업데이트하는 함수들을 포함하고 있습니다.

  이 파일은 플레이어의 상태를 관리하고, 움직임 및 상호작용을 처리합니다.

  플레이어의 상태에 따라 그려낼 프레임을 업데이트 합니다.

  - #### 주요 함수
    - `void set...State(Player *player)`: 키 입력시 호출하면 플레이어의 상태를 변경합니다.

- ### slime.c
  파일은 게임 내 슬라임 캐릭터의 동작과 상태를 관리하는 함수들을 포함하고 있습니다.

  이 파일은 슬라임의 생성, 이동, 충돌 처리 및 그리기 등의 기능을 제공합니다.

  - #### 주요 함수
    - `Slime createSlime(Vector2 position)`: 이 함수는 주어진 위치에서 새로운 슬라임을 생성합니다.
    - `void updateSlimePosition(Slime *slime, EnvItem *envItems, int envItemsLength)`: 슬라임의 움직임을 랜덤하게 업데이트합니다.
    - `void drawSlime(Slime *slime)`: 슬라임을 그려냅니다.
   
- ### linked_damage_list.c
  게임 내의 데미지 정보를 연결 리스트 구조로 관리하는 함수들을 포함하고 있습니다.
  
  이 파일은 데미지 리스트의 생성, 추가, 삭제 및 화면에 그리기 등의 기능을 제공합니다.

  - #### 주요 함수
    - `void append(DamageNode **head, Damage newData)`: 공격시 호출하며, 데미지노드를 추가합니다.
    - `void removeExpiredNode(DamageNode **head)`: 만료된 데미지 노드를 삭제합니다.
    - `void drawDamages(DamageNode **node)`: 리스트에 있는 데미지를 그려냅니다.
    - 
- ### texture.c
  파일은 다양한 텍스처를 생성하고, 환경 아이템을 이용해 텍스처를 그리는 기능을 포함하고 있습니다.

  - #### 주요 합수
    - `Texture2D get...Texture()`: 텍스쳐를 생성합니다.
    - `void draw...Texture(EnvItem envItem, Texture2D grassTexture, Texture2D dirtTexture)`: EnvItem을 사용하여 지정된 위치에 잔디와 흙 텍스처를 그립니다.
  
  
