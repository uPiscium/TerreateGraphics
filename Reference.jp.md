# GeoFrameとは
`GeoFrame`とは`glfw`と`glad`を利用したオープンソースの`OpenGL`ハンドラです。ウィンドウの作成や操作、シェーダを用いたバッファの描画、オフスクリーンレンダリング、フォントを用いたテキストの表示などの基本的な操作を行うことができます。また、独自のジョブシステムを用いたマルチスレッド実行もサポートしています。

-----

# 目次
- [型エイリアス一覧](#型エイリアス一覧)
- [例外](#例外)
- [Animation関連のクラス](#Animation関連のクラス)
- [BitFlag関連のクラス](#BitFlag関連のクラス)
- [Buffer関連のクラス](#buffer関連のクラス)
- [Event関連のクラス](#event関連のクラス)
- [Font関連のクラス](#font関連のクラス)
- [Job関連のクラス](#job関連のクラス)
- [Model関連のクラス](#model関連のクラス)
- [Object関連のクラス](#object関連のクラス)
- [Screen関連のクラス(WIP)](#screen関連のクラス)
- [Shader関連のクラス](#shader関連のクラス)
- [Skeleton関連のクラス](#skeleton関連のクラス)
- [Text関連のクラス](#text関連のクラス)
- [Window関連のクラス](#window関連のクラス)
- [Math関連のクラス](#math関連のクラス)

-----

# 型エイリアス一覧
## 基本型
- `bool -> TCbool`
- `int8_t -> TCi8`
- `uint8_t -> TCu8`
- `int16_t -> TCi16`
- `uint16_t -> TCu16`
- `int32_t -> TCi32`
- `uint32_t -> TCu32`
- `int64_t -> TCi64`
- `uint64_t -> TCu64`
- `float -> TCfloat`
- `double -> TCdouble`

- `TCbool -> Bool`
- `TCi8 -> Byte`
- `TCu8 -> Ubyte`
- `TCi16 -> Short`
- `TCu16 -> Ushort`
- `TCi32 -> Int`
- `TCu32 -> Uint`
- `TCi64 -> Long`
- `TCu64 -> Ulong`
- `TCfloat -> Float`
- `TCdouble -> Double`

- `std::mutex -> Mutex`
- `std::condition_variable -> CondVar`
- `std::thread -> Thread`
- `TCu32 -> ID`
- `TCu64 -> Index`
- `TCu64 -> EventID`
- `TCu64 -> Size`
- `std::string -> Str`
- `std::wstring -> WStr`
- `std::stringstream -> Stream`
- `std::ifstream -> InputFileStream`

- `Map = std::unordered_map<S, T>`
- `Pair = std::pair<T, T>`
- `Set = std::unordered_set<T>`
- `Shared = std::shared_ptr<T>`
- `Queue = std::queue<T, Container>`
- `UniqueLock = std::unique_lock<T>`
- `LockGuard = std::lock_guard<T>`
- `Atomic = std::atomic<T>`
- `Vec = std::vector<T>`
- `Function = std::function<T>`

- `ErrorCallback = std::function<void(int errorCode, char const *message)>`
- `MonitorCallback = std::function<void(GLFWmonitor *monitor, int event)>`
- `JoystickCallback = std::function<void(int joystickID, int event)>`

## `math`モジュール
- `complexT = Complex<T>`
- `fractionT = Fraction<T>`
- `matrixT = MatrixBase<T>`
- `vec2T = ColumnVector2D<T>`
- `vec3T = ColumnVector3D<T>`
- `vec4T = ColumnVector4D<T>`
- `mat2T = Matrix2x2<T>`
- `mat2x3T = Matrix2x3<T>`
- `mat2x4T = Matrix2x4<T>`
- `mat3x2T = Matrix3x2<T>`
- `mat3T = Matrix3x3<T>`
- `mat3x4T = Matrix3x4<T>`
- `mat4x2T = Matrix4x2<T>`
- `mat4x3T = Matrix4x3<T>`
- `mat4T = Matrix4x4<T>`
- `quaternionT = Quaternion<T>`

- `complex = complexT<Float>`
- `fraction = fractionT<Int>`
- `matrix = matrixT<Float>`
- `vec2 = vec2T<Float>`
- `vec3 = vec3T<Float>`
- `vec4 = vec4T<Float>`
- `mat2 = mat2T<Float>`
- `mat2x3 = mat2x3T<Float>`
- `mat2x4 = mat2x4T<Float>`
- `mat3x2 = mat3x2T<Float>`
- `mat3 = mat3T<Float>`
- `mat3x4 = mat3x4T<Float>`
- `mat4x2 = mat4x2T<Float>`
- `mat4x3 = mat4x3T<Float>`
- `mat4 = mat4T<Float>`
- `quaternion = quaternionT<Float>`

-----

# 例外
## CoreError
このエラーは`GeoFrame`の内部で発生したエラーを示します。このエラーは`GeoFrame`内部で発生するエラー全てで使用されます。

-----

# Animation関連のクラス
## 内容
- [Transformクラス](#Transformクラス)
- [Animationクラス(WIP)](#Animationクラス(WIP))

## Transformクラス
このクラスはアニメーションのキーフレーム情報を管理します。このクラスのインスタンスはアニメーションの対象となるオブジェクトに対して適用されます。\
主なメンバは以下の通りです。
- `scale` : スケールを示す`vec3`型の変数です。
- `position` : 位置を示す`vec3`型の変数です。
- `rotation` : 回転を示す`quaternion`型の変数です。

## Animationクラス(WIP)
このクラスはアニメーションを管理します。アニメーションの制御はこのクラスのメンバ関数を利用して行ってください。\
**このクラスは現在開発中です。アニメーションの再生や計算が正しく行われない可能性があります。バグ等が発生した場合は`upiscium@gmail.com`までご連絡ください。**\
主なメンバ関数は以下の通りです。
- `Animation()`
アニメーション管理用オブジェクトを生成します。
- `Str const &GetName() const`
アニメーションの名前を取得します。
- `Vec<Transform> const &GetKeyFrames() const`
アニメーションのキーフレームを取得します。
- `void SetName(Str const &name)`
アニメーションの名前を設定します。
- `void AddKeyFrame(Transform const &keyFrame, Float const &time)`
アニメーションにキーフレームを追加します。キーフレームの時間は`float`型で指定してください。
- `void RemoveKeyFrame(Uint const &index)`
アニメーションから指定したインデックスのキーフレームを削除します。
- `Transform Interpolate(Float const &time) const`
アニメーションの指定した時間のキーフレームを取得します。
- `Transform const &operator[](Uint const &index) const`
アニメーションの指定したインデックスのキーフレームを取得します。
- `Transform operator[](Float const &time) const`
アニメーションの指定した時間のキーフレームを取得します。
- `static mat4 TransformToMatrix(Transform const &transform)`
キーフレームデータを行列に変換します。

-----

# BitFlag関連のクラス
## 内容
- [BitFlagクラス](#BitFlagクラス)

## BitFlagクラス
このクラスはビットフラグを管理します。ビットフラグは`enum`型に対してビット演算を行ったときに自動変換されます。このクラスはビットフラグの操作を行うためのメンバ関数を提供します。\
主なメンバ関数は以下の通りです。(`T`は`enum`型)
- `void Set(T const &flag)`
ビットフラグを設定します。
- `void Set(Flag const &flag)`
ビットフラグを設定します。
- `void Unset(T const &flag)`
ビットフラグを解除します。
- `void Unset(Flag const &flag)`
ビットフラグを解除します。
- `void Toggle(T const &flag)`
ビットフラグを反転します。
- `void Toggle(Flag const &flag)`
ビットフラグを反転します。
- `Bool IsSet(T const &flag) const`
ビットフラグが設定されているかを取得します。
- `Bool IsSet(Flag const &flag) const`
ビットフラグが設定されているかを取得します。
- `void Clear()`
ビットフラグを全て解除します。

-----

# Buffer関連のクラス
## 内容
- [Attributeクラス](#Attributeクラス)
- [Bufferクラス](#Bufferクラス)
- [BufferUsage列挙体](#BufferUsage列挙体)
- [DrawMode列挙体](#DrawMode列挙体)
- [頂点属性](#頂点属性)

## Attributeクラス
このクラスは`OpenGL`の頂点属性に対する各設定値を保持します。各設定値の詳細は[頂点属性](#頂点属性)を参照してください。

- `Attribute(Ulong const &index, Ulong const &comps, Ulong const &stride, Ulong const &offset)`
頂点属性を生成します。
- `Ulong const &GetIndex() const`
頂点属性のインデックスを取得します。
- `Ulong const &GetComps() const`
頂点属性の要素数を取得します。
- `Ulong const &GetStride() const`
頂点属性のストライドを取得します。
- `Ulong const &GetOffset() const`
頂点属性のオフセットを取得します。
- `static Vec<Attribute> GenerateAttributes(Vec<Ulong> const &comps)`
各頂点属性の要素数から頂点属性を生成します。
- `static Vec<Attribute> GenerateAttributes(Vec<Ulong> const &comps, Vec<Ulong> const &offsets, Vec<Ulong> const &strides)`
各頂点属性の要素数、オフセット、ストライドから頂点属性を生成します。

## Bufferクラス
このクラスは`OpenGL`のバッファオブジェクトを制御します。バッファの`GPU`メモリへの送信及びバッファ内容の更新はこのクラスのメンバ関数を利用して行ってください。\
主なメンバ関数は以下の通りです。
- `Buffer(BufferUsage usage)`
OpenGLのバッファオブジェクトを生成します。バッファの使用方法は[BufferUsage](#BufferUsage列挙体)列挙体のメンバを指定してください。
- `BufferUsage const &GetUsage() const`
バッファのOpenGL上での使用方法を取得します。
- `void LoadVertices(Float const *data, Size const &size)`
バッファに頂点座標をロードします。頂点座標のデータは`float`型の配列で、配列のサイズを`Size`型で指定してください。
- `void LoadVertices(Vec<Float> const &data)`
バッファに頂点座標をロードします。頂点座標のデータは`float`型の`Vec`で指定してください。
- `void LoadIndices(Uint const *data, Size const &size)`
バッファにインデックスをロードします。インデックスのデータは`unsigned int`型の配列で、配列のサイズを`Size`型で指定してください。
- `void LoadIndices(Vec<Uint> const &data)`
バッファにインデックスをロードします。インデックスのデータは`unsigned int`型の`Vec`で指定してください。
- `void LoadAttributes(Attribute const *data, Size const &size)`
バッファに頂点属性をロードします。頂点属性のデータは`Attribute`型の配列で、配列のサイズを`Size`型で指定してください。
- `void LoadAttributes(Vec<Attribute> const &data)`
バッファに頂点属性をロードします。頂点属性のデータは`Attribute`型の`Vec`で指定してください。
- `void Draw(DrawMode const &drawMode)`
バッファにロードされたデータを描画します。描画モードは`DrawMode`列挙体のメンバを指定してください。
- `void DrawInstances(Size const &numInstances, DrawMode const &drawMode)`
バッファにロードされたデータを複数回描画します。描画回数は`Size`型で指定してください。描画モードは`DrawMode`列挙体のメンバを指定してください。

## BufferUsage列挙体
OpenGL上でのバッファの使用方法を指定するための列挙体です。列挙体のメンバは以下の通りです。
| メンバ | 用途 | 更新頻度 |
|:---:|-----|:---:|
| `STATIC_DRAW` | バッファの内容を**一度だけ**更新し、使用する | 低 |
| `STATIC_READ` | バッファの内容を**一度だけ**更新し、読み取る | 低 |
| `STATIC_COPY` | バッファの内容を**一度だけ**更新し、コピーする | 低 |
| `STREAM_DRAW` | バッファの内容を低頻度で更新し、使用する | 中 |
| `STREAM_READ` | バッファの内容を低頻度で更新し、読み取る | 中 |
| `STREAM_COPY` | バッファの内容を低頻度で更新し、コピーする | 中 |
| `DYNAMIC_DRAW` | バッファの内容を高頻度で更新し、使用する | 高 |
| `DYNAMIC_READ` | バッファの内容を高頻度で更新し、読み取る | 高 |
| `DYNAMIC_COPY` | バッファの内容を高頻度で更新し、コピーする | 高 |

## DrawMode列挙体
OpenGL上での描画モードを指定するための列挙体です。列挙体のメンバは以下の通りです。
| メンバ | 用途 |
|:---:|-----|
| `POINTS` | 各頂点を点として描画する |
| `LINES` | 各頂点を線として描画する |
| `LINE_LOOP` | 各頂点を線として描画し、最後の頂点と最初の頂点を結ぶ |
| `LINE_STRIP` | 各頂点を線として描画し、隣接する頂点を結ぶ |
| `TRIANGLES` | 各頂点を三角形として描画する |
| `TRIANGLE_STRIP` | 各頂点を三角形として描画し、隣接する頂点を結ぶ |
| `TRIANGLE_FAN` | 各頂点を三角形として描画し、最初の頂点と隣接する頂点を結ぶ |
| `QUADS` | 各頂点を四角形として描画する |

## 頂点属性
`OpenGL`のバッファはバッファ内のデータの切り分け方を指定するために頂点属性を一つ以上設定する必要があります。すべての頂点属性は`float`型に設定されます。他の型を利用する場合はシェーダー内で別の型に明示的に変換する処理を記述してください。頂点属性には四つの設定値があり、それぞれ以下の通りです。
- `Index` : 頂点属性のインデックスです。この頂点属性が先頭から何番目かを示す値で、頂点座標のインデックスは`0`から始まる整数値です。頂点座標のインデックスは`Attribute`クラスのコンストラクタの第一引数に渡すことで設定できます。`GenerateAttributes()`関数を利用した場合は自動生成されるため指定する必要はありません。
- `Components` : 頂点属性を構成する要素数です。頂点属性の要素数は`Attribute`クラスのコンストラクタの第二引数に渡すことで設定できます。
- `Stride(WIP)` : 頂点属性のストライドです。ストライドは頂点属性の要素間のバイト数を示す値で、`0`以上の整数値です。ストライドは`Attribute`クラスのコンストラクタの第三引数に渡すことで設定できます。`GenerateAttributes()`関数で省略した場合は、`Components`の要素から自動生成されます。
*//TODO:例を示す*
- `Offset` : 頂点属性のオフセットです。オフセットは頂点属性の先頭からのバイト数を示す値で、`0`以上の整数値です。オフセットは`Attribute`クラスのコンストラクタの第四引数に渡すことで設定できます。`GenerateAttributes()`関数で省略した場合は、`Components`の要素から自動生成されます。

-----

# Event関連のクラス
## 内容
- [EventSystemクラス](#EventSystemクラス)
- [イベントのフォーマット](#イベントのフォーマット)

## EventSystemクラス
このクラスはイベントの登録、管理及びコールバックの呼び出しを行います。このクラスの関数は全てスレッドセーフであり、複数スレッドから安全にアクセスできます。また、このクラスはトリガ関数の管理も行います。トリガ関数はコールバック関数型とは異なり、特定のイベントが最初に発生した一回のみ呼び出されます。イベントのフォーマット及びコールバック関数、トリガ関数のフォーマットの詳細は[イベントのフォーマット](#イベントのフォーマット)を参照してください。\
主なメンバ関数は以下の通りです。
- `EventSystem()`
イベントシステムを初期化します。
- `void Register(Str const &event, EventCallback const &callback)`
イベントに対するコールバック関数を登録します。コールバックはイベントが発生するたびに呼び出されます。
- `void AddTrigger(Str const &event, EventCallback const &callback)`
イベントに対するトリガ関数を登録します。トリガ関数はイベントが発生した最初の一回のみ呼び出されます。
- `void ProcessEvents()`
登録されたイベントを処理します。この関数はイベントの発行を待機し、発行されたイベントに対して登録されたコールバック関数及びトリガ関数を呼び出します。
- `void PublishEvent(Str const &event)`
イベントを発行します。発行されたイベントに対して登録されたコールバック関数及びトリガ関数が呼び出すには`ProcessEvents()`関数を呼び出してください。

## イベントのフォーマット
イベントは`EventSystem`クラスの`PostEvent`関数を利用して発行します。
イベントとして発行できる型は`Str`型のみで、イベントのフォーマットは特に決まっていませんが以下のフォーマットを推奨します。
- `****:****:****:**** ...`
- `****/****/****/**** ...`

※ `****`の部分に任意の文字列を入力

イベントのコールバック関数は`EventSystem`クラスの`RegisterCallback()`関数を利用して登録します。コールバック関数は以下のフォーマットである必要があります。
- `Function<void(Str const &event)>`\
※ `event`には発行されたイベントが格納されます

また、イベントのトリガ関数は`EventSystem`クラスの`RegisterTrigger()`関数を利用して登録します。トリガ関数はコールバックと同様のフォーマットである必要があります。

-----

# Font関連のクラス
## 内容
- [Character構造体](#Character構造体)
- [Fontクラス](#Fontクラス)

## Character構造体
この構造体はフォントの文字情報を保持します。この構造体のメンバは全て`public`ですが、書き換えた場合の動作は保証されないため書き換えは行わないことをおすすめします。\
主なメンバは以下の通りです。
- `Uint codepoint` : ユニコードのコードポイントを示す整数値です。
- `Shared<Texture> texture` : 文字のテクスチャを示す`Texture`クラスのインスタンスです。
- `Pair<Uint> size` : 文字本体のサイズを示す`Pair`クラスのインスタンスです。(Width, Height)の順で格納されます。
- `Pair<Uint> bearing` : 文字の各軸からの距離を示す`Pair`クラスのインスタンスです。(X, Y)の順で格納されます。
- `Long advance` : 文字の表示時の幅を示す整数値です。

## Fontクラス
このクラスは外部からフォントファイルを読み込み、文字情報を管理します。フォントの制御はこのクラスのメンバ関数を利用して行ってください。\
主なメンバ関数は以下の通りです。
- `Font(Str const &path, Uint const &size)`
フォントファイルを読み込みます。フォントファイルのパスとフォントのサイズを指定してください。
- `Uint GetFontSize() const`
フォントのサイズを取得します。
- `Shared<Character> const &GetCharacter(wchar_t const &character)`
指定した文字の情報を取得します。取得しようとした文字が存在しない場合の動作は保証されません。
- `Shared<Character> const &AcquireCharacter(wchar_t const &character) const`
指定した文字の情報を取得します。取得しようとした文字が存在しない場合はエラーが発生します。
- `Pair<Uint> AcquireTextSize(WStr const &text) const`
指定したテキストの描画サイズを取得します。(Width, Height)の順で格納されます。
- `Vec<Shared<Character>> AcquireCharacters(WStr const &text) const`
指定したテキストの各文字の情報を取得します。
- `void LoadCharacter(wchar_t const &character)`
指定した文字の情報を読み込みます。
- `void LoadText(WStr const &text)`
指定したテキストの各文字の情報を読み込みます。

-----

# Job関連のクラス
## 内容
- [IJobクラス](#IJobクラス)
- [SimpleJobクラス](#SimpleJobクラス)
- [JobSystemクラス](#JobSystemクラス)
- [Job対応関数フォーマット](#Job対応関数フォーマット)

## IJobクラス
このクラスは`JobSystem`にジョブとして登録するための基底クラスです。このクラスを継承して`Execute`メソッドを実装することでジョブを作成してください。`JobSystem`はこのクラスを継承したクラスのインスタンスをジョブとして扱います。また、ジョブ同士の依存関係を設定したい場合は依存関係を設定したいジョブのインスタンスをコンストラクタに渡してください。コンストラクタ以外から依存関係を定義することはできません。\
主なメンバ関数は以下の通りです。
- `JobBase()`
ジョブを生成します。
- `JobBase(JobBase *dependency)`
依存関係を設定してジョブを生成します。このジョブは指定したジョブの完了後に実行されます。
- `JobBase(Vec<JobBase *> const &dependencies)`
依存関係を設定してジョブを生成します。このジョブは指定したジョブの全ての完了後に実行されます。
- `Bool IsExecutable() const`
このジョブが実行可能かを取得します。このジョブが依存するジョブが全て完了している場合に`true`を返します。
- `Bool IsFinished() const`
このジョブが完了しているかを取得します。このジョブが実行された後に`true`を返します。
- `virtual void Execute()`
このジョブの実行内容を記述します。この関数は`operator()`を通して`JobSystem`によって呼び出されます。

## SimpleJobクラス
このクラスは`IJob`クラスを継承したジョブクラスです。このクラスは渡された関数オブジェクトをジョブとして実行します。このクラスのインスタンスを作成する際には関数オブジェクトを渡してください。実行可能な関数のフォーマットは[Job対応関数フォーマット](#job対応関数フォーマット)を参照してください。\
主なメンバ関数は以下の通りです。
- `SimpleJob()`
関数オブジェクトを持たないジョブを生成します。
- `SimpleJob(Function<void()> const &target)`
関数オブジェクトを持つジョブを生成します。
- `SimpleJob(Function<void()> const &target, JobBase *const dependency)`
依存関係を設定して関数オブジェクトを持つジョブを生成します。このジョブは指定したジョブの完了後に実行されます。
- `SimpleJob(Function<void()> const &target, Vec<JobBase *> const &dependencies)`
依存関係を設定して関数オブジェクトを持つジョブを生成します。このジョブは指定したジョブの全ての完了後に実行されます。
- `virtual void Execute() override`
関数オブジェクトを実行します。

## JobSystemクラス
このクラスはマルチスレッド実行をサポートするためのクラスです。このクラスの関数は全てスレッドセーフであり、複数スレッドから安全にアクセスできます。特定の関数のマルチスレッド実行を行いたい場合はこのクラスを利用してください。また、関数をデーモン化したい場合もこのクラスを利用してください。\
主なメンバ関数は以下の通りです。
- `JobSystem(Uint const &numThreads = std::thread::hardware_concurrency())`
ジョブシステムを初期化します。スレッド数を指定しない場合はハードウェアのスレッド数が使用されます。
- `virtual void Stop()`
ジョブシステムを停止します。この関数を呼び出すとジョブシステムは停止し、新しいジョブの実行を停止します。既に実行中のジョブは完了するまで実行を続けます。
- `virtual void Schedule(JobBase *job)`
ジョブをスケジュールします。この関数を呼び出すとジョブシステムは指定したジョブをキューに追加し順次実行します。
- `virtual void Daemonize(JobBase *job))`
ジョブをデーモン化します。この関数を呼び出すとジョブシステムは指定したジョブを即時にデーモンスレッドを生成し実行します。
- `virtual void WaitForAll()`
ジョブシステムが実行中のジョブが全て完了するまで待機します。この関数を呼び出すとジョブシステムは全てのジョブが完了するまで待機します。

## Job対応関数フォーマット
`SimpleJob`クラスで実行可能な関数のフォーマットは以下の通りです。
- `Function<void()>`\
このフォーマットの関数は引数及び戻り値を持つことができないため、引数または戻り値を持つ関数を実行したい場合はラムダ式を利用し参照を経由して操作を行ってください。 \
以下は引数を持つ関数を実行する例です。
```cpp
// 引数を持つ関数を擬似的に実行する
Int value = 0;
Function<void()> func = [&value]() {
  value = 1;
};
SimpleJob job(func);
```

-----

# Model関連のクラス
## 内容
- [ColorProperty列挙体](#ColorProperty列挙体)
- [FloatProperty列挙体](#FloatProperty列挙体)
- [TextureProperty列挙体](#TextureProperty列挙体)
- [MaterialDataクラス](#MaterialDataクラス)
- [MeshDataクラス](#MeshDataクラス)
- [Meshクラス](#Meshクラス)
- [Modelクラス](#Modelクラス)

## ColorProperty列挙体
この列挙体はマテリアルのカラープロパティを示すための列挙体です。\
列挙体のメンバは以下の通りです。
| メンバ | 用途 |
|:---:|-----|
| `AMBIENT` | 環境光の色 |
| `DIFFUSE` | 拡散光の色 |
| `SPECULAR` | 鏡面反射光の色 |
| `EMISSIVE` | 放射光の色 |

## FloatProperty列挙体
この列挙体はマテリアルの定数プロパティを示すための列挙体です。\
列挙体のメンバは以下の通りです。
| メンバ | 用途 |
|:---:|-----|
| `SHININESS` | 光沢度 |
| `TRANSPARENCY` | 透明度 |
| `REFLECTIVITY` | 反射率 |
| `REFRACTIVITY` | 屈折率 |

## TextureProperty列挙体
この列挙体はマテリアルのテクスチャプロパティを示すための列挙体です。\
列挙体のメンバは以下の通りです。
| メンバ | 用途 |
|:---:|-----|
| `NORMAL` | 法線マップ |
| `AMBIENT` | 環境光マップ |
| `DIFFUSE` | 拡散光マップ |
| `SPECULAR` | 鏡面反射光マップ |
| `EMISSIVE` | 放射光マップ |
| `DISSOLVE` | 透明度マップ |
| `SHININESS` | 光沢度マップ |
| `REFLECTION` | 反射マップ |
| `REFRACTION` | 屈折マップ |

## MaterialDataクラス
このクラスはマテリアルの情報を保持します。マテリアルの情報は`OpenGL`のシェーダに送信するためのデータを保持します。\
主なメンバ関数は以下の通りです。
- `MaterialData()`
マテリアルデータを保持するオブジェクトを生成します。
- `Str const &GetName() const`
マテリアルの名前を取得します。
- `vec4 const &GetColorProperty(ColorProperty const &property) const`
マテリアルのカラープロパティを取得します。
- `Float const &GetFloatProperty(FloatProperty const &property) const`
マテリアルのフロートプロパティを取得します。
- `TextureMap GetTextureProperty(TextureProperty const &property) const`
マテリアルのテクスチャプロパティを取得します。
- `void SetName(Str const &name)`
マテリアルの名前を設定します。
- `void SetColorProperty(ColorProperty const &property, vec4 const &value)`
マテリアルのカラープロパティを設定します。
- `void SetFloatProperty(FloatProperty const &property, Float const &value)`
マテリアルの定数プロパティを設定します。
- `void SetTextureProperty(TextureProperty const &property, TextureMap value)`
マテリアルのテクスチャプロパティを設定します。
- `bool HasColorProperty(ColorProperty const &property) const`
マテリアルが指定したカラープロパティを持っているかを取得します。
- `bool HasFloatProperty(FloatProperty const &property) const`
マテリアルが指定したフロートプロパティを持っているかを取得します。
- `bool HasTextureProperty(TextureProperty const &property) const`
マテリアルが指定したテクスチャプロパティを持っているかを取得します。
- `void RemoveColorProperty(ColorProperty const &property)`
マテリアルのカラープロパティを削除します。
- `void RemoveFloatProperty(FloatProperty const &property)`
マテリアルのフロートプロパティを削除します。
- `void RemoveTextureProperty(TextureProperty const &property)`
マテリアルのテクスチャプロパティを削除します。
- `void ClearColorProperties()`
マテリアルのカラープロパティを全て削除します。
- `void ClearFloatProperties()`
マテリアルのフロートプロパティを全て削除します。
- `void ClearTextureProperties()`
マテリアルのテクスチャプロパティを全て削除します。

## MeshDataクラス
このクラスはメッシュの情報を保持します。メッシュの情報は`OpenGL`のシェーダに送信するためのデータを保持します。\
主なメンバ関数は以下の通りです。
- `MeshData(BufferUsage const &usage = BufferUsage::STATIC_DRAW)`
- `BufferUsage const &GetUsage() const`
- `ModelFlag GetFlag() const`
- `Int const &GetMaterial() const`
- `Vec<Uint> const &GetIndices() const`
- `Vec<Float> const &AcquireVertices()`
- `void SetFlag(ModelFlag const &flag)`
- `Bool HasNormals() const`
- `Bool HasUVs() const`
- `Bool HasColors() const`
- `Bool HasJoint() const`
- `Bool HasWeight() const`
- `Bool HasMaterial() const`
- `Bool HasMorph() const`
- `void LoadFlag(ModelFlag const &flags)`
- `void LoadVertices(Vec<Float> const &vertices)`
- `void LoadIndices(Vec<Uint> const &indices)`
- `void LoadMaterial(Int const &material)`
- `void LoadVertexSet(Vec<Vec<Uint>> const &sets)`
- `void LoadPosition(Vec<Vec<Float>> const &position)`
- `void LoadNormal(Vec<Vec<Float>> const &normal)`
- `void LoadUV(Vec<Vec<Float>> const &uv)`
- `void LoadColor(Vec<Vec<Float>> const &color)`
- `void LoadJoint(Vec<Vec<Float>> const &joint)`
- `void LoadWeight(Vec<Vec<Float>> const &weight)`
- `void LoadMorph(Vec<Vec<Float>> const &morph)`
- `void Construct()`

-----

# Object関連のクラス

-----

# Screen関連のクラス
## 内容
- [Screenクラス](#Screenクラス)
- [~~CubeScreenクラス~~](#CubeScreenクラス)

## Screenクラス
このクラスは`OpenGL`のフレームバッファを管理します。フレームバッファの作成及び描画はこのクラスのメンバ関数を利用して行ってください。オフスクリーンレンダリング、ポストエフェクト、マルチスクリーンなどの機能の他に、デプスバッファの作成機能もサポートしています。スクリーンのレンダリング結果はメンバ関数を用いて取得することができます。また、デプスバッファ及びステンシルバッファは使用できません。代わりにカラーバッファにデプス及びステンシルのデータを保存してください。\
*現在複数のテクスチャバッファを持つスクリーンの描画は動作しません。(代わりに単一のテクスチャバッファを持つスクリーンを複数使用してください。)*\
主なメンバ関数は以下の通りです。

## CubeScreenクラス //未実装
*このクラスは実装予定であり、現在は未実装のため利用できません。*\
~~このクラスは`OpenGL`のキューブマップを管理します。キューブマップの作成及び描画はこのクラスのメンバ関数を利用して行ってください。スクリーンと同様にオフスクリーンレンダリング、ポストエフェクト、マルチスクリーンなどの機能をサポートしています。また、デプスバッファの作成機能もサポートしています。~~\
~~主なメンバ関数は以下の通りです。~~

-----

# Shader関連のクラス
## 内容
- [Shaderクラス](#Shaderクラス)

## Shaderクラス
このクラスはGLSL言語で記述されたプログラムを読み込み、シェーダとして管理します。また、深度バッファやステンシルバッファといったOpenGLの機能の有効、無効の管理、シェーダに対する変数の送信を行います。\
主なメンバ関数は以下の通りです。

-----

# Skeleton関連のクラス

-----

# Text関連のクラス

-----

# Window関連のクラス
## 内容
- [Iconクラス](#Iconクラス)
- [Cursorクラス](#Cursorクラス)
- [StandardCursorクラス](#StandardCursorクラス)
- [WindowSettings構造体](#WindowSettings構造体)
- [WindowControllerクラス](#WindowControllerクラス)
- [Windowクラス](#Windowクラス)

## Iconクラス
このクラスはウィンドウのアイコンを管理します。アイコンの画像の読み込みはこのクラスのメンバ関数を利用して行ってください。\
主なメンバ関数は以下の通りです。

## Cursorクラス
このクラスはカーソルを管理します。独自の外観を持つカーソルの作成及び描画はこのクラスのメンバ関数を利用して行ってください。\
主なメンバ関数は以下の通りです。

## StandardCursorクラス
このクラスは標準のカーソルを管理します。標準のカーソルの作成及び描画はこのクラスのメンバ関数を利用して行ってください。標準のカーソルの種類は以下の通りです。次に示す定数はすべて`CursorShape`列挙体のメンバです。
| 定数 | カーソルの種類 |
|:---:|:---:|
| `ARROW` | 矢印カーソル |
| `IBEAM` | Iビームカーソル |
| `CROSSHAIR` | 十字カーソル |
| `HAND` | 手カーソル |
| `HRESIZE` | 水平リサイズカーソル |
| `VRESIZE` | 垂直リサイズカーソル |

主なメンバ関数は以下の通りです。

## WindowSettings構造体
この構造体はウィンドウの設定を保持します。この構造体のメンバは全て`public`であり、この構造体のメンバを書き換えた上で`Window`クラスに渡すことでウィンドウの設定を変更できます。
それぞれのメンバの詳細は以下の通りです。
| メンバ | 用途 | デフォルト値 |
|:---:|-----|:---:|
| `resizable` | 画面のサイズが変更可能かを設定します | `GLFW_TRUE` |
| `visible` | 画面の表示/非表示を設定します | `GLFW_TRUE` |
| `decorated` | 画面上部のボタン等を付けるかどうかを設定します | `GLFW_TRUE` |
| `focused` | 画面が非最大化されて生成されたときに入力フォーカスが与えられるかどうかを設定します | `GLFW_TRUE` |
| `autoIconify` | 画面が入力フォーカスを失ったときに全画面化が自動的に解除され、アイコン化されるかを設定します | `GLFW_TRUE` |
| `floating` | 画面が常に最前面に表示されるかを設定します | `GLFW_FALSE` |
| `maximized` | 画面が生成時に最大化されるかを設定します | `GLFW_FALSE` |
| `centerCursor` | 全画面生成時にカーソルを中央に配置するかを設定します | `GLFW_TRUE` |
| `transparentFramebuffer` | 画面のフレームバッファが透明かどうかを設定します | `GLFW_FALSE` |
| `focusOnShow` | `Window::Show()`が呼び出されたときに画面に入力フォーカスをあてるかを設定します | `GLFW_TRUE` |
| `scaleToMonitor` | 画面のコンテンツ領域を、それが配置されているモニターのコンテンツスケールに基づいてサイズ変更するかどうかを設定します | `GLFW_FALSE` |

## WindowControllerクラス
このクラスはウィンドウの各種コールバック関数及び毎フレームの処理を行う関数を管理します。ウィンドウのコールバック関数及び毎フレームの処理はこのクラスを継承し実装することで行ってください。`OnFrame()`関数は必ずオーバーライドしてください。他のコールバックはデフォルトでは何も行いません。\
オーバーライド可能なコールバック関数は以下の通りです。

## Windowクラス
このクラスはウィンドウを管理します。ウィンドウの作成及び描画はこのクラスのメンバ関数を利用して行ってください。また、ウィンドウの設定は`WindowSettings`構造体を利用して行ってください。ウィンドウに対する操作等もこのクラスのメンバ関数を利用して行ってください。\
主なメンバ関数は以下の通りです。

-----

# Math関連のクラス

-----
