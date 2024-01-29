# GeoFrameとは
GeoFrameとはglfwとgladを利用したオープンソースのOpenGLハンドラです。ウィンドウの作成や操作、シェーダを用いたバッファの描画、オフスクリーンレンダリング、フォントを用いたテキストの表示などの基本的な操作を行うことができます。また、独自のジョブシステムを用いたマルチスレッド実行もサポートしています。その他にもイベントハンドラやサーバー·クライアントベースのネットワークシステム、外部オブジェクトファイルのインポート·エクスポートもサポートします。ネットワークシステム及び外部オブジェクトファイルのインポート·エクスポートは現在開発中のため動作が不安定です。組み込んで使用する際は注意してください。

# 目次
- [型エイリアス一覧](#型エイリアス一覧)
- [例外一覧](#例外一覧)
- [Buffer関連のクラス](# 
- [Event関連のクラス](# 
- [Font関連のクラス](# 
- [Job関連のクラス](# 
- [Screen関連のクラス](# 

# 型エイリアス一覧
## 基本型の型エイリアス
- ID = unsigned
- Index = unsigned long long
- EventID = unsigned long long

## stdの型エイリアス
- Map = std::unordered_map
- Pair = std::pair
- Set = std::unordered_set
- Shared = std::shared_ptr
- Queue = std::queue
- UniqueLock = std::unique_lock
- LockGuard = std::lock_guard
- Atomic = std::atomic
- Vec = std::vector
- Function = std::function
- Mutex = std::mutex
- Thread = std::thread
- CondVar = std::condition_variable
- Str = std::string
- WStr = std::wstring

## GeoMathの型エイリアス
- vec2T = GeoMath::vec2
- vec3T = GeoMath::vec3
- vec4T = GeoMath::vec4
- mat2T = GeoMath::mat2
- mat2x3T = GeoMath::mat2x3
- mat2x4T = GeoMath::mat2x4
- mat3x2T = GeoMath::mat3x2
- mat3T = GeoMath::mat3
- mat3x4T = GeoMath::mat3x4
- mat4x2T = GeoMath::mat4x2
- mat4x3T = GeoMath::mat4x3
- mat4T = GeoMath::mat4
- QuaternionT = GeoMath::Quaternion
- vec2 = vec2T
- vec3 = vec3T
- vec4 = vec4T
- mat2 = mat2T
- mat2x3 = mat2x3T
- mat2x4 = mat2x4T
- mat3x2 = mat3x2T
- mat3 = mat3T
- mat3x4 = mat3x4T
- mat4x2 = mat4x2T
- mat4x3 = mat4x3T
- mat4 = mat4T
- Quaternion = QuaternionT

# 例外一覧
## APIError
このエラーはOpenGLのAPIライブラリであるgladもしくはglfwが実行に失敗した場合に発生します。また、このエラーはgladもしくはglfwの初期化が失敗した場合にも発生します。

## KernelError
このエラーはGeoFrame内部のクラスが何らかの理由で正常な動作を行えなかった場合に発生します。その原因は様々であるため、エラーメッセージを参照してください。

## InterfaceError
このエラーはGeoFrameのオブジェクトに対して不正な引数を渡した場合や、不正な操作を行った場合に発生します。

# Buffer関連のクラス
## Attributeクラス
このクラスはOpenGLの頂点属性に対する各設定値を保持します。各設定値の詳細は[頂点属性]を参照してください。
主なメンバ関数は以下の通りです。

## Bufferクラス
このクラスはOpenGLのバッファオブジェクトを制御します。バッファのGPUメモリへの送信及びバッファ内容の更新はこのクラスのメンバ関数を利用して行ってください。
主なメンバ関数は以下の通りです。

# Event関連のクラス
## EventSystemクラス
このクラスはイベントの登録、管理及びコールバックの呼び出しを行います。このクラスの関数は全てスレッドセーフであり、複数スレッドから安全にアクセスできます。イベント駆動形式のプログラムを作成する場合はこのクラスを利用してください。イベントのフォーマット等の詳細は[イベント]を参照してください。
主なメンバ関数は以下の通りです。

# Font関連のクラス
## Character構造体
この構造体はフォントの文字情報を保持します。この構造体のメンバは全てpublicです。
主なメンバは以下の通りです。

## Fontクラス
このクラスは外部からフォントファイルを読み込み、文字情報を管理します。フォントの制御はこのクラスのメンバ関数を利用して行ってください。
主なメンバ関数は以下の通りです。

# Job関連のクラス
## IJobクラス
このクラスはJobSystemにジョブとして登録するための基底クラスです。このクラスを継承してExecuteメソッドを実装することでジョブを作成してください。JobSystemはこのクラスを継承したクラスのインスタンスをジョブとして扱います。また、ジョブ同士の依存関係を設定したい場合は依存関係を設定したいジョブのインスタンスをコンストラクタに渡してください。コンストラクタ以外から依存関係を定義することはできません。
主なメンバ関数は以下の通りです。

## SimpleJobクラス
このクラスはIJobクラスを継承したジョブクラスです。このクラスは渡された関数オブジェクトをジョブとして実行します。このクラスのインスタンスを作成する際には関数オブジェクトを渡してください。ただし、実行可能な関数は返り値と引数を設定できないためラムダ式(無名関数)を用いて実行したい関数をラップして渡すようにしてください。
主なメンバ関数は以下の通りです。

## JobSystemクラス
このクラスはマルチスレッド実行をサポートするためのクラスです。このクラスの関数は全てスレッドセーフであり、複数スレッドから安全にアクセスできます。マルチスレッド実行を行いたい場合はこのクラスを利用してください。
主なメンバ関数は以下の通りです。

# Screen関連のクラス

