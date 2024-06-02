# GeoFrameとは
`GeoFrame`とは`glfw`と`glad`を利用したオープンソースの`OpenGL`ハンドラです.ウィンドウの作成や操作,シェーダを用いたバッファの描画,オフスクリーンレンダリング,フォントを用いたテキストの表示などの基本的な操作を行うことができます.また,独自のジョブシステムを用いたマルチスレッド実行もサポートしています.

-----

# 目次
- [型エイリアス一覧](#型エイリアス一覧)
- [例外](#例外)
- [Animation関連のクラス](#animation関連のクラス)
- [BitFlag関連のクラス](#bitFlag関連のクラス)
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
- [Texture関連のクラス](#texture関連のクラス)
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

- `Map = std::unordered_map<S,T>`
- `Pair = std::pair<T,T>`
- `Set = std::unordered_set<T>`
- `Shared = std::shared_ptr<T>`
- `Queue = std::queue<T,Container>`
- `UniqueLock = std::unique_lock<T>`
- `LockGuard = std::lock_guard<T>`
- `Atomic = std::atomic<T>`
- `Vec = std::vector<T>`
- `Function = std::function<T>`

- `ErrorCallback = std::function<void(int errorCode,char const *message)>`
- `MonitorCallback = std::function<void(GLFWmonitor *monitor,int event)>`
- `JoystickCallback = std::function<void(int joystickID,int event)>`

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
このエラーは`GeoFrame`の内部で発生したエラーを示します.このエラーは`GeoFrame`内部で発生するエラー全てで使用されます.

-----

# Animation関連のクラス
## 内容
- [Transformクラス](#Transformクラス)
- [Animationクラス(WIP)](#Animationクラス(WIP))

## Transformクラス
このクラスはアニメーションのキーフレーム情報を管理します.このクラスのインスタンスはアニメーションの対象となるオブジェクトに対して適用されます.\
主なメンバは以下の通りです.
- `scale` : スケールを示す`vec3`型の変数です.
- `position` : 位置を示す`vec3`型の変数です.
- `rotation` : 回転を示す`quaternion`型の変数です.

## Animationクラス(WIP)
このクラスはアニメーションを管理します.アニメーションの制御はこのクラスのメンバ関数を利用して行ってください.\
**このクラスは現在開発中です.アニメーションの再生や計算が正しく行われない可能性があります.バグ等が発生した場合は`upiscium@gmail.com`までご連絡ください.**\
主なメンバ関数は以下の通りです.
- `Animation()`\
アニメーション管理用オブジェクトを生成します.
- `Str const &GetName() const`\
アニメーションの名前を取得します.
- `Vec<Transform> const &GetKeyFrames() const`\
アニメーションのキーフレームを取得します.
- `void SetName(Str const &name)`\
アニメーションの名前を設定します.
- `void AddKeyFrame(Transform const &keyFrame,Float const &time)`\
アニメーションにキーフレームを追加します.キーフレームの時間は`float`型で指定してください.
- `void RemoveKeyFrame(Uint const &index)`\
アニメーションから指定したインデックスのキーフレームを削除します.
- `Transform Interpolate(Float const &time) const`\
アニメーションの指定した時間のキーフレームを取得します.
- `Transform const &operator[](Uint const &index) const`\
アニメーションの指定したインデックスのキーフレームを取得します.
- `Transform operator[](Float const &time) const`\
アニメーションの指定した時間のキーフレームを取得します.
- `static mat4 TransformToMatrix(Transform const &transform)`\
キーフレームデータを行列に変換します.

-----

# BitFlag関連のクラス
## 内容
- [BitFlagクラス](#BitFlagクラス)

## BitFlagクラス
このクラスはビットフラグを管理します.ビットフラグは`enum`型に対してビット演算を行ったときに自動変換されます.このクラスはビットフラグの操作を行うためのメンバ関数を提供します.\
主なメンバ関数は以下の通りです.(`T`は`enum`型)
- `void Set(T const &flag)`\
ビットフラグを設定します.
- `void Set(Flag const &flag)`\
ビットフラグを設定します.
- `void Unset(T const &flag)`\
ビットフラグを解除します.
- `void Unset(Flag const &flag)`\
ビットフラグを解除します.
- `void Toggle(T const &flag)`\
ビットフラグを反転します.
- `void Toggle(Flag const &flag)`\
ビットフラグを反転します.
- `Bool IsSet(T const &flag) const`\
ビットフラグが設定されているかを取得します.
- `Bool IsSet(Flag const &flag) const`\
ビットフラグが設定されているかを取得します.
- `void Clear()`\
ビットフラグを全て解除します.

-----

# Buffer関連のクラス
## 内容
- [Attributeクラス](#Attributeクラス)
- [Bufferクラス](#Bufferクラス)
- [BufferUsage列挙体](#BufferUsage列挙体)
- [DrawMode列挙体](#DrawMode列挙体)
- [頂点属性](#頂点属性)

## Attributeクラス
このクラスは`OpenGL`の頂点属性に対する各設定値を保持します.各設定値の詳細は[頂点属性](#頂点属性)を参照してください.

- `Attribute(Ulong const &index,Ulong const &comps,Ulong const &stride,Ulong const &offset)`\
頂点属性を生成します.
- `Ulong const &GetIndex() const`\
頂点属性のインデックスを取得します.
- `Ulong const &GetComps() const`\
頂点属性の要素数を取得します.
- `Ulong const &GetStride() const`\
頂点属性のストライドを取得します.
- `Ulong const &GetOffset() const`\
頂点属性のオフセットを取得します.
- `static Vec<Attribute> GenerateAttributes(Vec<Ulong> const &comps)`\
各頂点属性の要素数から頂点属性を生成します.
- `static Vec<Attribute> GenerateAttributes(Vec<Ulong> const &comps,Vec<Ulong> const &offsets,Vec<Ulong> const &strides)`\
各頂点属性の要素数,オフセット,ストライドから頂点属性を生成します.

## Bufferクラス
このクラスは`OpenGL`のバッファオブジェクトを制御します.バッファの`GPU`メモリへの送信及びバッファ内容の更新はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Buffer(BufferUsage usage)`\
OpenGLのバッファオブジェクトを生成します.バッファの使用方法は[BufferUsage](#BufferUsage列挙体)列挙体のメンバを指定してください.
- `BufferUsage const &GetUsage() const`\
バッファのOpenGL上での使用方法を取得します.
- `void LoadVertices(Float const *data,Size const &size)`\
バッファに頂点座標をロードします.頂点座標のデータは`float`型の配列で,配列のサイズを`Size`型で指定してください.
- `void LoadVertices(Vec<Float> const &data)`\
バッファに頂点座標をロードします.頂点座標のデータは`float`型の`Vec`で指定してください.
- `void LoadIndices(Uint const *data,Size const &size)`\
バッファにインデックスをロードします.インデックスのデータは`unsigned int`型の配列で,配列のサイズを`Size`型で指定してください.
- `void LoadIndices(Vec<Uint> const &data)`\
バッファにインデックスをロードします.インデックスのデータは`unsigned int`型の`Vec`で指定してください.
- `void LoadAttributes(Attribute const *data,Size const &size)`\
バッファに頂点属性をロードします.頂点属性のデータは`Attribute`型の配列で,配列のサイズを`Size`型で指定してください.
- `void LoadAttributes(Vec<Attribute> const &data)`\
バッファに頂点属性をロードします.頂点属性のデータは`Attribute`型の`Vec`で指定してください.
- `void Draw(DrawMode const &drawMode)`\
バッファにロードされたデータを描画します.描画モードは`DrawMode`列挙体のメンバを指定してください.
- `void DrawInstances(Size const &numInstances,DrawMode const &drawMode)`\
バッファにロードされたデータを複数回描画します.描画回数は`Size`型で指定してください.描画モードは`DrawMode`列挙体のメンバを指定してください.

## BufferUsage列挙体
OpenGL上でのバッファの使用方法を指定するための列挙体です.列挙体のメンバは以下の通りです.
| メンバ | 用途 | 更新頻度 |
|:---:|-----|:---:|
| `STATIC_DRAW` | バッファの内容を**一度だけ**更新し,使用する | 低 |
| `STATIC_READ` | バッファの内容を**一度だけ**更新し,読み取る | 低 |
| `STATIC_COPY` | バッファの内容を**一度だけ**更新し,コピーする | 低 |
| `STREAM_DRAW` | バッファの内容を低頻度で更新し,使用する | 中 |
| `STREAM_READ` | バッファの内容を低頻度で更新し,読み取る | 中 |
| `STREAM_COPY` | バッファの内容を低頻度で更新し,コピーする | 中 |
| `DYNAMIC_DRAW` | バッファの内容を高頻度で更新し,使用する | 高 |
| `DYNAMIC_READ` | バッファの内容を高頻度で更新し,読み取る | 高 |
| `DYNAMIC_COPY` | バッファの内容を高頻度で更新し,コピーする | 高 |

## DrawMode列挙体
OpenGL上での描画モードを指定するための列挙体です.列挙体のメンバは以下の通りです.
| メンバ | 用途 |
|:---:|-----|
| `POINTS` | 各頂点を点として描画する |
| `LINES` | 各頂点を線として描画する |
| `LINE_LOOP` | 各頂点を線として描画し,最後の頂点と最初の頂点を結ぶ |
| `LINE_STRIP` | 各頂点を線として描画し,隣接する頂点を結ぶ |
| `TRIANGLES` | 各頂点を三角形として描画する |
| `TRIANGLE_STRIP` | 各頂点を三角形として描画し,隣接する頂点を結ぶ |
| `TRIANGLE_FAN` | 各頂点を三角形として描画し,最初の頂点と隣接する頂点を結ぶ |
| `QUADS` | 各頂点を四角形として描画する |

## 頂点属性
`OpenGL`のバッファはバッファ内のデータの切り分け方を指定するために頂点属性を一つ以上設定する必要があります.すべての頂点属性は`float`型に設定されます.他の型を利用する場合はシェーダー内で別の型に明示的に変換する処理を記述してください.頂点属性には四つの設定値があり,それぞれ以下の通りです.
- `Index` : 頂点属性のインデックスです.この頂点属性が先頭から何番目かを示す値で,頂点座標のインデックスは`0`から始まる整数値です.頂点座標のインデックスは`Attribute`クラスのコンストラクタの第一引数に渡すことで設定できます.`GenerateAttributes()`関数を利用した場合は自動生成されるため指定する必要はありません.
- `Components` : 頂点属性を構成する要素数です.頂点属性の要素数は`Attribute`クラスのコンストラクタの第二引数に渡すことで設定できます.
- `Stride(WIP)` : 頂点属性のストライドです.ストライドは頂点属性の要素間のバイト数を示す値で,`0`以上の整数値です.ストライドは`Attribute`クラスのコンストラクタの第三引数に渡すことで設定できます.`GenerateAttributes()`関数で省略した場合は,`Components`の要素から自動生成されます.
*//TODO:例を示す*
- `Offset` : 頂点属性のオフセットです.オフセットは頂点属性の先頭からのバイト数を示す値で,`0`以上の整数値です.オフセットは`Attribute`クラスのコンストラクタの第四引数に渡すことで設定できます.`GenerateAttributes()`関数で省略した場合は,`Components`の要素から自動生成されます.

-----

# Event関連のクラス
## 内容
- [EventSystemクラス](#EventSystemクラス)
- [イベントのフォーマット](#イベントのフォーマット)

## EventSystemクラス
このクラスはイベントの登録,管理及びコールバックの呼び出しを行います.このクラスの関数は全てスレッドセーフであり,複数スレッドから安全にアクセスできます.また,このクラスはトリガ関数の管理も行います.トリガ関数はコールバック関数型とは異なり,特定のイベントが最初に発生した一回のみ呼び出されます.イベントのフォーマット及びコールバック関数,トリガ関数のフォーマットの詳細は[イベントのフォーマット](#イベントのフォーマット)を参照してください.\
主なメンバ関数は以下の通りです.
- `EventSystem()`\
イベントシステムを初期化します.
- `void Register(Str const &event,EventCallback const &callback)`\
イベントに対するコールバック関数を登録します.コールバックはイベントが発生するたびに呼び出されます.
- `void AddTrigger(Str const &event,EventCallback const &callback)`\
イベントに対するトリガ関数を登録します.トリガ関数はイベントが発生した最初の一回のみ呼び出されます.
- `void ProcessEvents()`\
登録されたイベントを処理します.この関数はイベントの発行を待機し,発行されたイベントに対して登録されたコールバック関数及びトリガ関数を呼び出します.
- `void PublishEvent(Str const &event)`\
イベントを発行します.発行されたイベントに対して登録されたコールバック関数及びトリガ関数が呼び出すには`ProcessEvents()`関数を呼び出してください.

## イベントのフォーマット
イベントは`EventSystem`クラスの`PostEvent`関数を利用して発行します.
イベントとして発行できる型は`Str`型のみで,イベントのフォーマットは特に決まっていませんが以下のフォーマットを推奨します.
- `****:****:****:**** ...`
- `****/****/****/**** ...`

※ `****`の部分に任意の文字列を入力

イベントのコールバック関数は`EventSystem`クラスの`RegisterCallback()`関数を利用して登録します.コールバック関数は以下のフォーマットである必要があります.
- `Function<void(Str const &event)>`\
※ `event`には発行されたイベントが格納されます

また,イベントのトリガ関数は`EventSystem`クラスの`RegisterTrigger()`関数を利用して登録します.トリガ関数はコールバックと同様のフォーマットである必要があります.

-----

# Font関連のクラス
## 内容
- [Character構造体](#Character構造体)
- [Fontクラス](#Fontクラス)

## Character構造体
この構造体はフォントの文字情報を保持します.この構造体のメンバは全て`public`ですが,書き換えた場合の動作は保証されないため書き換えは行わないことをおすすめします.\
主なメンバは以下の通りです.
- `Uint codepoint` : ユニコードのコードポイントを示す整数値です.
- `Shared<Texture> texture` : 文字のテクスチャを示す`Texture`クラスのインスタンスです.
- `Pair<Uint> size` : 文字本体のサイズを示す`Pair`クラスのインスタンスです.(Width,Height)の順で格納されます.
- `Pair<Uint> bearing` : 文字の各軸からの距離を示す`Pair`クラスのインスタンスです.(X,Y)の順で格納されます.
- `Long advance` : 文字の表示時の幅を示す整数値です.

## Fontクラス
このクラスは外部からフォントファイルを読み込み,文字情報を管理します.フォントの制御はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Font(Str const &path,Uint const &size)`\
フォントファイルを読み込みます.フォントファイルのパスとフォントのサイズを指定してください.
- `Uint GetFontSize() const`\
フォントのサイズを取得します.
- `Shared<Character> const &GetCharacter(wchar_t const &character)`\
指定した文字の情報を取得します.取得しようとした文字が存在しない場合の動作は保証されません.
- `Shared<Character> const &AcquireCharacter(wchar_t const &character) const`\
指定した文字の情報を取得します.取得しようとした文字が存在しない場合はエラーが発生します.
- `Pair<Uint> AcquireTextSize(WStr const &text) const`\
指定したテキストの描画サイズを取得します.(Width,Height)の順で格納されます.
- `Vec<Shared<Character>> AcquireCharacters(WStr const &text) const`\
指定したテキストの各文字の情報を取得します.
- `void LoadCharacter(wchar_t const &character)`\
指定した文字の情報を読み込みます.
- `void LoadText(WStr const &text)`\
指定したテキストの各文字の情報を読み込みます.

-----

# Job関連のクラス
## 内容
- [IJobクラス](#IJobクラス)
- [SimpleJobクラス](#SimpleJobクラス)
- [JobSystemクラス](#JobSystemクラス)
- [Job対応関数フォーマット](#Job対応関数フォーマット)

## IJobクラス
このクラスは`JobSystem`にジョブとして登録するための基底クラスです.このクラスを継承して`Execute`メソッドを実装することでジョブを作成してください.`JobSystem`はこのクラスを継承したクラスのインスタンスをジョブとして扱います.また,ジョブ同士の依存関係を設定したい場合は依存関係を設定したいジョブのインスタンスをコンストラクタに渡してください.コンストラクタ以外から依存関係を定義することはできません.\
主なメンバ関数は以下の通りです.
- `JobBase()`\
ジョブを生成します.
- `JobBase(JobBase *dependency)`\
依存関係を設定してジョブを生成します.このジョブは指定したジョブの完了後に実行されます.
- `JobBase(Vec<JobBase *> const &dependencies)`\
依存関係を設定してジョブを生成します.このジョブは指定したジョブの全ての完了後に実行されます.
- `Bool IsExecutable() const`\
このジョブが実行可能かを取得します.このジョブが依存するジョブが全て完了している場合に`true`を返します.
- `Bool IsFinished() const`\
このジョブが完了しているかを取得します.このジョブが実行された後に`true`を返します.
- `virtual void Execute()`\
このジョブの実行内容を記述します.この関数は`operator()`を通して`JobSystem`によって呼び出されます.

## SimpleJobクラス
このクラスは`IJob`クラスを継承したジョブクラスです.このクラスは渡された関数オブジェクトをジョブとして実行します.このクラスのインスタンスを作成する際には関数オブジェクトを渡してください.実行可能な関数のフォーマットは[Job対応関数フォーマット](#job対応関数フォーマット)を参照してください.\
主なメンバ関数は以下の通りです.
- `SimpleJob()`\
関数オブジェクトを持たないジョブを生成します.
- `SimpleJob(Function<void()> const &target)`\
関数オブジェクトを持つジョブを生成します.
- `SimpleJob(Function<void()> const &target,JobBase *const dependency)`\
依存関係を設定して関数オブジェクトを持つジョブを生成します.このジョブは指定したジョブの完了後に実行されます.
- `SimpleJob(Function<void()> const &target,Vec<JobBase *> const &dependencies)`\
依存関係を設定して関数オブジェクトを持つジョブを生成します.このジョブは指定したジョブの全ての完了後に実行されます.
- `virtual void Execute() override`\
関数オブジェクトを実行します.

## JobSystemクラス
このクラスはマルチスレッド実行をサポートするためのクラスです.このクラスの関数は全てスレッドセーフであり,複数スレッドから安全にアクセスできます.特定の関数のマルチスレッド実行を行いたい場合はこのクラスを利用してください.また,関数をデーモン化したい場合もこのクラスを利用してください.\
主なメンバ関数は以下の通りです.
- `JobSystem(Uint const &numThreads = std::thread::hardware_concurrency())`\
ジョブシステムを初期化します.スレッド数を指定しない場合はハードウェアのスレッド数が使用されます.
- `virtual void Stop()`\
ジョブシステムを停止します.この関数を呼び出すとジョブシステムは停止し,新しいジョブの実行を停止します.既に実行中のジョブは完了するまで実行を続けます.
- `virtual void Schedule(JobBase *job)`\
ジョブをスケジュールします.この関数を呼び出すとジョブシステムは指定したジョブをキューに追加し順次実行します.
- `virtual void Daemonize(JobBase *job))`\
ジョブをデーモン化します.この関数を呼び出すとジョブシステムは指定したジョブを即時にデーモンスレッドを生成し実行します.
- `virtual void WaitForAll()`\
ジョブシステムが実行中のジョブが全て完了するまで待機します.この関数を呼び出すとジョブシステムは全てのジョブが完了するまで待機します.

## Job対応関数フォーマット
`SimpleJob`クラスで実行可能な関数のフォーマットは以下の通りです.
- `Function<void()>`\
このフォーマットの関数は引数及び戻り値を持つことができないため,引数または戻り値を持つ関数を実行したい場合はラムダ式を利用し参照を経由して操作を行ってください.\
以下は引数を持つ関数を実行する例です.
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
この列挙体はマテリアルのカラープロパティを示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 用途 |
|:---:|-----|
| `AMBIENT` | 環境光の色 |
| `DIFFUSE` | 拡散光の色 |
| `SPECULAR` | 鏡面反射光の色 |
| `EMISSIVE` | 放射光の色 |

## FloatProperty列挙体
この列挙体はマテリアルの定数プロパティを示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 用途 |
|:---:|-----|
| `SHININESS` | 光沢度 |
| `TRANSPARENCY` | 透明度 |
| `REFLECTIVITY` | 反射率 |
| `REFRACTIVITY` | 屈折率 |

## TextureProperty列挙体
この列挙体はマテリアルのテクスチャプロパティを示すための列挙体です.\
列挙体のメンバは以下の通りです.
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
このクラスはマテリアルの情報を保持します.マテリアルの情報は`OpenGL`のシェーダに送信するためのデータを保持します.\
主なメンバ関数は以下の通りです.
- `MaterialData()`\
マテリアルデータを保持するオブジェクトを生成します.
- `Str const &GetName() const`\
マテリアルの名前を取得します.
- `vec4 const &GetColorProperty(ColorProperty const &property) const`\
マテリアルのカラープロパティを取得します.
- `Float const &GetFloatProperty(FloatProperty const &property) const`\
マテリアルのフロートプロパティを取得します.
- `TextureMap GetTextureProperty(TextureProperty const &property) const`\
マテリアルのテクスチャプロパティを取得します.
- `void SetName(Str const &name)`\
マテリアルの名前を設定します.
- `void SetColorProperty(ColorProperty const &property,vec4 const &value)`\
マテリアルのカラープロパティを設定します.
- `void SetFloatProperty(FloatProperty const &property,Float const &value)`\
マテリアルの定数プロパティを設定します.
- `void SetTextureProperty(TextureProperty const &property,TextureMap value)`\
マテリアルのテクスチャプロパティを設定します.
- `bool HasColorProperty(ColorProperty const &property) const`\
マテリアルが指定したカラープロパティを持っているかを取得します.
- `bool HasFloatProperty(FloatProperty const &property) const`\
マテリアルが指定したフロートプロパティを持っているかを取得します.
- `bool HasTextureProperty(TextureProperty const &property) const`\
マテリアルが指定したテクスチャプロパティを持っているかを取得します.
- `void RemoveColorProperty(ColorProperty const &property)`\
マテリアルのカラープロパティを削除します.
- `void RemoveFloatProperty(FloatProperty const &property)`\
マテリアルのフロートプロパティを削除します.
- `void RemoveTextureProperty(TextureProperty const &property)`\
マテリアルのテクスチャプロパティを削除します.
- `void ClearColorProperties()`\
マテリアルのカラープロパティを全て削除します.
- `void ClearFloatProperties()`\
マテリアルのフロートプロパティを全て削除します.
- `void ClearTextureProperties()`\
マテリアルのテクスチャプロパティを全て削除します.

## MeshDataクラス
このクラスはメッシュの情報を保持します.メッシュの情報は`OpenGL`のシェーダに送信するためのデータを保持します.\
主なメンバ関数は以下の通りです.
- `MeshData(BufferUsage const &usage = BufferUsage::STATIC_DRAW)`\
メッシュデータを保持するオブジェクトを生成します.バッファの使用方法は[BufferUsage](#BufferUsage列挙体)列挙体のメンバを指定してください.
- `BufferUsage const &GetUsage() const`\
メッシュデータのバッファの使用方法を取得します.
- `ModelFlag GetFlag() const`\
メッシュデータのフラグを取得します.
- `Shared<MaterialData> const &GetMaterial() const`\
メッシュデータのマテリアルデータを取得します.
- `Vec<Uint> const &GetIndices() const`\
メッシュデータのインデックスを取得します.
- `Vec<Float> const &AcquireVertices()`\
メッシュデータの頂点座標を取得します.
- `void SetFlag(ModelFlag const &flag)`\
メッシュデータのフラグを設定します.
- `Bool HasNormals() const`\
メッシュデータが法線を持っているかを取得します.
- `Bool HasUVs() const`\
メッシュデータがUV座標を持っているかを取得します.
- `Bool HasColors() const`\
メッシュデータが色情報を持っているかを取得します.
- `Bool HasJoint() const`\
メッシュデータがジョイント情報を持っているかを取得します.
- `Bool HasWeight() const`\
メッシュデータがウェイト情報を持っているかを取得します.
- `Bool HasMaterial() const`\
メッシュデータがマテリアル情報を持っているかを取得します.
- `Bool HasMorph() const`\
メッシュデータがモーフ情報を持っているかを取得します.
- `void LoadFlag(ModelFlag const &flags)`\
メッシュデータのフラグを設定します.
- `void LoadVertices(Vec<Float> const &vertices)`\
メッシュデータの頂点座標を設定します.
- `void LoadIndices(Vec<Uint> const &indices)`\
メッシュデータのインデックスを設定します.
- `void LoadMaterial(Shared<MaterialData> const &material)`\
メッシュデータのマテリアルデータを設定します.
- `void LoadVertexSet(Vec<Vec<Uint>> const &sets)`\
メッシュデータの頂点セットを設定します.
- `void LoadPosition(Vec<Vec<Float>> const &position)`\
メッシュデータの頂点座標を設定します.
- `void LoadNormal(Vec<Vec<Float>> const &normal)`\
メッシュデータの法線を設定します.
- `void LoadUV(Vec<Vec<Float>> const &uv)`\
メッシュデータのUV座標を設定します.
- `void LoadColor(Vec<Vec<Float>> const &color)`\
メッシュデータの色情報を設定します.
- `void LoadJoint(Vec<Vec<Float>> const &joint)`\
メッシュデータのジョイント情報を設定します.
- `void LoadWeight(Vec<Vec<Float>> const &weight)`\
メッシュデータのウェイト情報を設定します.
- `void LoadMorph(Vec<Vec<Float>> const &morph)`\
メッシュデータのモーフ情報を設定します.
- `void Construct()`\
メッシュデータを構築します.`LoadVertices()`関数を利用した場合は実行の必要はありません.\
また,この関数を実行する前に最低でも`LoadPosition()`,`LoadVertexSet()`関数を実行してください.

## Meshクラス
このクラスはメッシュを管理します.メッシュの描画はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Mesh()`\
メッシュを管理するオブジェクトを生成します.
- `Mesh(MeshData &data)`\
メッシュデータを指定してメッシュを生成します.
- `Mesh(Mesh const &other)`\
メッシュをコピーしてメッシュを生成します.
- `BufferUsage const &GetUsage() const`\
メッシュデータのバッファの使用方法を取得します.
- `Shared<MaterialData> const &GetMaterial()`\
メッシュデータのマテリアルデータを取得します.
- `ModelFlag GetFlag() const`\
メッシュデータのフラグを取得します.
- `void LoadData(MeshData &data)`\
メッシュデータを設定します.複数回設定する場合は呼び出し毎に前回のデータは破棄されます.\
また,高頻度でデータを設定する場合は`MeshData`クラスの`BufferUsage`を`BufferUsage::DYNAMIC_DRAW`に設定することをおすすめします.
- `void Draw() const`\
メッシュを描画します.
- `static Vec<Core::Attribute> GenerateAttributes(ModelFlag const &flag)`\
メッシュデータのフラグから頂点属性を生成します.

## Modelクラス
このクラスはモデルを管理します.モデルの描画はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Model()`\
モデルを管理するオブジェクトを生成します.
- `Vec<Mesh> const &GetMeshes() const`\
モデルのメッシュデータを取得します.
- `Vec<Shared<MaterialData>> const &GetMaterials() const`\
モデルのマテリアルデータを取得します.
- `void AddMesh(Mesh const &mesh)`\
モデルにメッシュデータを追加します.
- `void AddMaterial(Shared<MaterialData> const &material)`\
モデルにマテリアルデータを追加します.
- `void Draw() const`\
モデルを描画します.

-----

# Object関連のクラス
## 内容
- [UUIDクラス](#UUIDクラス)
- [Objectクラス](#Objectクラス)

## UUIDクラス
このクラスはUUID(Universally Unique Identifier)を生成します.UUIDは一意の識別子を生成するためのクラスです.\
`TerreateCore`ライブラリ内で生成されるオブジェクトにはUUIDが付与されます.\
主なメンバ関数は以下の通りです.
- `UUID()`\
UUIDを生成します.
- `UUID(const UUID &other)`\
UUIDをコピーしてUUIDを生成します.
- `Byte const *GetUUID() const`\
UUIDのバイト列を取得します.
- `Str ToString() const;`\
UUIDの文字列を取得します.
- `static UUID FromChar(Byte const *uuid)`\
UUIDのバイト列からUUIDを生成します.
- `static UUID FromString(Str const &uuid)`\
UUIDの文字列からUUIDを生成します.

また,UUIDは`==`演算子をサポートしている他,`std::hash<UUID>`をサポートしています.

## Objectクラス
このクラスは`TerreateCore`ライブラリ内の全てのオブジェクトの基底クラスです.このクラスは全てのオブジェクトにUUIDを付与します.\
主なメンバ関数は以下の通りです.
- `Object()`\
オブジェクトを生成します.
- `UUID const &GetUUID() const`\
オブジェクトのUUIDを取得します.

-----

# Screen関連のクラス
## 内容
- [Screenクラス](#Screenクラス)
- [~~CubeScreenクラス~~](#CubeScreenクラス)

## Screenクラス
このクラスは`OpenGL`のフレームバッファを管理します.フレームバッファの作成及び描画はこのクラスのメンバ関数を利用して行ってください.オフスクリーンレンダリング,ポストエフェクト,マルチスクリーンなどの機能の他に,デプスバッファの作成機能もサポートしています.スクリーンのレンダリング結果はメンバ関数を用いて取得することができます.また,デプスバッファ及びステンシルバッファは使用できません.代わりにカラーバッファにデプス及びステンシルのデータを保存してください.\
*現在複数のテクスチャバッファを持つスクリーンの描画は動作しません.(代わりに単一のテクスチャバッファを持つスクリーンを複数使用してください.)*\
主なメンバ関数は以下の通りです.
-  `Screen(Uint const &width,Uint const &height)`\
指定されたサイズのスクリーンを生成します.
-  `Uint GetWidth() const`\
スクリーンの幅を取得します.
-  `Uint GetHeight() const`\
スクリーンの高さを取得します.
-  `Shared<Texture> const &GetTexture() const`\
スクリーンの描画情報格納先テクスチャを取得します.
-  `void Transcript(Screen const &screen) const`\
指定されたスクリーンの描画情報をこのスクリーンに転写します.
-  `void ReadOnlyBind() const`\
スクリーンを読み取り専用で描画対象に設定します.
-  `void DrawOnlyBind() const`\
スクリーンを書き込み専用で描画対象に設定します.
-  `void Bind() const`\
スクリーンの描画対象として設定します.
-  `void Unbind() const`\
スクリーンを描画対象から解除します.
-  `void Fill(Vec<Float> const &color) const`\
スクリーンを指定された色で塗りつぶします.
-  `void Clear() const`\
スクリーンのバッファを全てクリアします.スクリーンを塗りつぶした場合はこの関数の実行時に色が変更されます.

## CubeScreenクラス //未実装
*このクラスは実装予定であり,現在は未実装のため利用できません.*\
~~このクラスは`OpenGL`のキューブマップを管理します.キューブマップの作成及び描画はこのクラスのメンバ関数を利用して行ってください.スクリーンと同様にオフスクリーンレンダリング,ポストエフェクト,マルチスクリーンなどの機能をサポートしています.また,デプスバッファの作成機能もサポートしています.~~\
~~主なメンバ関数は以下の通りです.~~

-----

# Shader関連のクラス
## 内容
- [BlendingFunction列挙体](#BlendingFunction列挙体)
- [CullingFace列挙体](#CullingFace列挙体)
- [CullingMode列挙体](#CullingMode列挙体)
- [DepthFunction列挙体](#DepthFunction列挙体)
- [StencilFunction列挙体](#StencilFunction列挙体)
- [StencilOperation列挙体](#StencilOperation列挙体)
- [GLFeature列挙体](#GLFeature列挙体)
- [ShaderOption構造体](#ShaderOption構造体)
- [Shaderクラス](#Shaderクラス)

## BlendingFunction列挙体
この列挙体は入力された色情報と背景の色情報との色混合に使用する関数を示すための列挙体です.\
このメンバで指定された数値が各色情報に対して適用(掛け算)されます.\
列挙体のメンバは以下の通りです.\
※ `($R_s$,$G_s$,$B_s$,$A_s$)`は入力された色情報,`($R_d$,$G_d$,$B_d$,$A_d)`は背景の色情報を示します.\
※ `($R_{max}$,$G_{max}$,$B_{max}$,$A_{max})`はそれぞれの色情報の値の最大値を示します.\
※ `($R_c$,$G_c$,$B_c$,$A_c$)`はある定数の色情報の値を示します.\
※ `i`は`$min(A_s,A_{max}-A_d)/A_{max}$`を示します.
| メンバ | 適用される数値 / (r,g,b,a) |
| `ZERO` | `(0,0,0,0)` |
| `ONE` | `(1,1,1,1)` |
| `SRC_COLOR` | `($R_s/R_{max}$,$G_s/G_{max}$,$B_s/B_{max}$,$A_s/A_{max}$)` |
| `ONE_MINUS_SRC_COLOR` | `($1-R_s/R_{max}$,$1-G_s/G_{max}$,$1-B_s/B_{max}$,$1-A_s/A_{max}$)` |
| `DST_COLOR` | `($R_d/R_{max}$,$G_d/G_{max}$,$B_d/B_{max}$,$A_d/A_{max}$)` |
| `ONE_MINUS_DST_COLOR` | `($1-R_d/R_{max}$,$1-G_d/G_{max}$,$1-B_d/B_{max}$,$1-A_d/A_{max}$)` |
| `SRC_ALPHA` | `($A_s/A_{max}$,$A_s/A_{max}$,$A_s/A_{max}$,$A_s/A_{max}$)` |
| `ONE_MINUS_SRC_ALPHA` | `($1-A_s/A_{max}$,$1-A_s/A_{max}$,$1-A_s/A_{max}$,$1-A_s/A_{max}$)` |
| `DST_ALPHA` | `($A_d/A_{max}$,$A_d/A_{max}$,$A_d/A_{max}$,$A_d/A_{max}$)` |
| `ONE_MINUS_DST_ALPHA` | `($1-A_d/A_{max}$,$1-A_d/A_{max}$,$1-A_d/A_{max}$,$1-A_d/A_{max}$)` |
| `CONSTANT_COLOR` | `($R_c$,$G_c$,$B_c$,$A_c$)` |
| `ONE_MINUS_CONSTANT_COLOR` | `($1-R_c$,$1-G_c$,$1-B_c$,$1-A_c$)` |
| `CONSTANT_ALPHA` | `($A_c$,$A_c$,$A_c$,$A_c$)` |
| `ONE_MINUS_CONSTANT_ALPHA` | `($1-A_c$,$1-A_c$,$1-A_c$,$1-A_c$)` |
| `SRC_ALPHA_SATURATE` | `($i$,$i$,$i$,1)` |

## CullingFace列挙体
この列挙体は描画時にスキップする面を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `FRONT` | 前面を描画対象から除外します |
| `BACK` | 裏面を描画対象から除外します |
| `FRONT_AND_BACK` | 前面と裏面を描画対象から除外します |

## CullingMode列挙体
この列挙体は面を構成する頂点を前面から見たときの定義順序を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `CW` | 時計回りの順序で面の前面を定義します |
| `CCW` | 反時計回りの順序で面の前面を定義します |

## DepthFunction列挙体
この列挙体は深度テスト時に使用する関数を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `NEVER` | 描画を行いません |
| `LESS` | 深度値が小さい場合のみ描画します |
| `EQUAL` | 深度値が等しい場合のみ描画します |
| `LEQUAL` | 深度値が小さいか等しい場合のみ描画します |
| `GREATER` | 深度値が大きい場合のみ描画します |
| `NOTEQUAL` | 深度値が等しくない場合のみ描画します |
| `GEQUAL` | 深度値が大きいか等しい場合のみ描画します |
| `ALWAYS` | 常に描画します |

## StencilFunction列挙体
この列挙体はステンシルテスト時に使用する関数を示すための列挙体です.\
列挙体のメンバは以下の通りです.\
※ `$V_{ref}$`は`stencilRef`,`$V_{mask}`は`stencilMask`,`$V_s$`はステンシルバッファに格納されている値を示します.
| メンバ | 説明 |
|:---:|-----|
| `NEVER` | ステンシルテストは常に失敗します |
| `LESS` | `$V_{ref} & V_{mask} < V_s & V_{mask}$`の場合にステンシルテストが成功します |
| `EQUAL` | `$V_{ref} & V_{mask} = V_s & V_{mask}$`の場合にステンシルテストが成功します |
| `LEQUAL` | `$V_{ref} & V_{mask} <= V_s & V_{mask}$`の場合にステンシルテストが成功します |
| `GREATER` | `$V_{ref} & V_{mask} > V_s & V_{mask}$`の場合にステンシルテストが成功します |
| `NOTEQUAL` | `$V_{ref} & V_{mask} != V_s & V_{mask}$`の場合にステンシルテストが成功します |
| `GEQUAL` | `$V_{ref} & V_{mask} >= V_s & V_{mask}$`の場合にステンシルテストが成功します |
| `ALWAYS` | ステンシルテストは常に成功します |

## StencilOperation列挙体
この列挙体はステンシルテストが成功した場合のステンシルバッファの値の操作を示すための列挙体です.\
列挙体のメンバは以下の通りです.\
※ `$V_{ref}$`は`stencilRef`を示します.
| メンバ | 説明 |
|:---:|-----|
| `KEEP` | ステンシルバッファの値を変更しません |
| `ZERO` | ステンシルバッファの値を`0`に設定します |
| `REPLACE` | ステンシルバッファの値を`$V_{ref}`に設定します |
| `INCR` | ステンシルバッファの値をインクリメントします |
| `INCR_WRAP` | ステンシルバッファの値をインクリメントします.値が最大値を超えた場合は`0`に設定します |
| `DECR` | ステンシルバッファの値をデクリメントします |
| `DECR_WRAP` | ステンシルバッファの値をデクリメントします.値が最小値を下回った場合は最大値に設定します |
| `INVERT` | ステンシルバッファの値をビット反転します |

## GLFeature列挙体
この列挙体はOpenGLの機能を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 用途 |
|:---:|-----|
| `BLEND` | アルファ値を用いた背景との色混合を有効化します |
| `CULL_FACE` | `cullFace`で指定された面の描画をスキップする機能を有効化します |
| `DEPTH_TEST` | 深度テストを有効化します |
| `DITHER` | ディザリングを有効化します |
| `POLYGON_OFFSET_FILL` | ポリゴンオフセットを有効化します |
| `SAMPLE_ALPHA_TO_COVERAGE` | アルファ値を用いたサンプリングを有効化します |
| `SAMPLE_COVERAGE` | サンプリングを有効化します |
| `STENCIL_TEST` | ステンシルテストを有効化します |
| `SCISSOR_TEST` | シザーテストを有効化します |

## ShaderOption構造体
この構造体はシェーダのオプションを保持します.シェーダのオプションはシェーダの使用時に適用されます.\
構造体のメンバは以下の通りです.
| メンバ | 用途 | デフォルト値 |
|:---:|-----|:---:|
| `blending` | アルファ値を用いた背景との色混合を行うかを設定します | `true` |
| `culling` | `cullFace`で指定された面の描画をスキップするかを設定します | `false` |
| `depth` | 深度テストを行うかを設定します(無効化した状態で3Dオブジェクトを描画すると前後関係が考慮されない描画結果になります) | `true` |
| `scissor` | シザーテストを行うかを設定します | `false` |
| `stencil` | ステンシルテストを行うかを設定します | `false` |
| `src` | `blending`が有効な場合に描画されるオブジェクトの色データに対する操作を設定します | `BlendingFuntion::ONE` |
| `dst` | `blending`が有効な場合に描画先の色データに対する操作を設定します | `BlendingFuntion::ZERO` |
| `cullFace` | `culling`が有効な場合に描画をスキップする面を設定します | `CullingFace::BACK` |
| `frontFace` | `culling`が有効な場合に前面になる面を設定します | `CullingMode::CCW` |
| `depthFunc` | `depth`が有効な場合に`z`の値によってどのように判定を行うかを設定します | `DepthFunction::LESS` |
| `stencilFunc` | `stencil`が有効な場合にステンシルバッファの値によってどのように判定を行うかを設定します | `StencilFunction::ALWAYS` |
| `stencilRef` | `stencil`が有効な場合に`stencilMask`とAND演算される値を設定します | `0` |
| `stencilMask` | `stencil`が有効な場合に`stencilRef`とステンシルバッファの値にAND演算されるマスクを設定します | `0xFF` |
| `sFail` | ステンシルテストが失敗した場合のステンシルバッファの値の操作を設定します | `StencilOperation::KEEP` |
| `dpFail` | デプステストが失敗した場合のステンシルバッファの値の操作を設定します | `StencilOperation::KEEP` |
| `dpPass` | デプステストが成功した場合のステンシルバッファの値の操作を設定します | `StencilOperation::KEEP` |

## Shaderクラス
このクラスはGLSL言語で記述されたプログラムを読み込み,シェーダとして管理します.また,深度バッファやステンシルバッファといったOpenGLの機能の有効,無効の管理,シェーダに対する変数の送信を行います.`vec*`型,`mat*`型の詳細については[Math関連のクラス](#math関連のクラス)を参照してください.\
主なメンバ関数は以下の通りです.
- `Shader()`\
GLSLシェーダを生成します.
- `unsigned GetLocation(Str const &name) const`\
シェーダ内の変数の位置を取得します.
- `void SetBool(Str const &name,Bool const &value) const`\
シェーダー内の変数`name`に`Bool`型の値を送信します.
- `void SetBools(Str const &name,Bool const *value,Int const &count) const`\
シェーダー内の配列変数`name`に`Bool`型の配列を送信します.
- `void SetInt(Str const &name,Int const &value) const`\
シェーダー内の変数`name`に`Int`型の値を送信します.
- `void SetInts(Str const &name,Int const *value,Int const &count) const`\
シェーダー内の配列変数`name`に`Int`型の配列を送信します.
- `void SetFloat(Str const &name,Float const &value) const`\
シェーダー内の変数`name`に`Float`型の値を送信します.
- `void SetFloats(Str const &name,Float const *value,Int const &count) const`\
シェーダー内の配列変数`name`に`Float`型の配列を送信します.
- `void SetVec2(Str const &name,vec2 const &value) const`\
シェーダー内の配列変数`name`に`vec2`型の値を送信します.
- `void SetVec3(Str const &name,vec3 const &value) const`\
シェーダー内の配列変数`name`に`vec3`型の値を送信します.
- `void SetVec4(Str const &name,vec4 const &value) const`\
シェーダー内の配列変数`name`に`vec4`型の値を送信します.
- `void SetMat2(Str const &name,mat2 const &value) const`\
シェーダー内の配列変数`name`に`mat2`型の値を送信します.
- `void SetMat2x3(Str const &name,mat2x3 const &value) const`\
シェーダー内の配列変数`name`に`mat2x3`型の値を送信します.
- `void SetMat2x4(Str const &name,mat2x4 const &value) const`\
シェーダー内の配列変数`name`に`mat2x4`型の値を送信します.
- `void SetMat3x2(Str const &name,mat3x2 const &value) const`\
シェーダー内の配列変数`name`に`mat3x2`型の値を送信します.
- `void SetMat3(Str const &name,mat3 const &value) const`\
シェーダー内の配列変数`name`に`mat3`型の値を送信します.
- `void SetMat3x4(Str const &name,mat3x4 const &value) const`\
シェーダー内の配列変数`name`に`mat3x4`型の値を送信します.
- `void SetMat4x2(Str const &name,mat4x2 const &value) const`\
シェーダー内の配列変数`name`に`mat4x2`型の値を送信します.
- `void SetMat4x3(Str const &name,mat4x3 const &value) const`\
シェーダー内の配列変数`name`に`mat4x3`型の値を送信します.
- `void SetMat4(Str const &name,mat4 const &value) const`\
シェーダー内の配列変数`name`に`mat4`型の値を送信します.
- `void SetBlending(BlendingFuntion const &src,BlendingFuntion const &dst)`\
シェーダーの色混合関数を設定します.\
`BlendingFuntion`の詳細については[BlendingFunction列挙体](#BlendingFunction列挙体)を参照してください.
- `void SetCullingFace(CullingFace const &face,CullingMode const &frontFace = CullingMode::CCW)`\
シェーダーの描画対象から除外する面を設定します.\
`CullingFace`の詳細については[CullingFace列挙体](#CullingFace列挙体)を参照してください.\
`CullingMode`の詳細については[CullingMode列挙体](#CullingMode列挙体)を参照してください.
- `void SetDepth(DepthFunction const &func)`\
シェーダーの深度テスト関数を設定します.\
`DepthFunction`の詳細については[DepthFunction列挙体](#DepthFunction列挙体)を参照してください.
- `void SetStencilFunction(StencilFunction const &func,Int const &ref,Uint const &mask)`\
シェーダーのステンシルテスト関数を設定します.\
`StencilFunction`の詳細については[StencilFunction列挙体](#StencilFunction列挙体)を参照してください.
- `void SetStencilOperation(StencilOperation const &sFail,StencilOperation const &dpFail,StencilOperation const &dpPass)`\
シェーダーのステンシルバッファの値の操作を設定します.\
`StencilOperation`の詳細については[StencilOperation列挙体](#StencilOperation列挙体)を参照してください.
- `void AddVertexShaderSource(Str const &source)`\
シェーダーに頂点シェーダのソースコードを追加します.
- `void AddFragmentShaderSource(Str const &source)`\
シェーダーにフラグメントシェーダのソースコードを追加します.
- `void AddGeometryShaderSource(Str const &source)`\
シェーダーにジオメトリシェーダのソースコードを追加します.
- `void UseBlending(Bool const &value)`\
シェーダーの色混合を有効化,無効化を設定します.
- `void UseCulling(Bool const &value)`\
シェーダーの描画対象から除外する面を有効化,無効化を設定します.
- `void UseDepth(Bool const &value)`\
シェーダーの深度テストを有効化,無効化を設定します.
- `void UseScissor(Bool const &value)`\
シェーダーのシザーテストを有効化,無効化を設定します.
- `void UseStencil(Bool const &value)`\
シェーダーのステンシルテストを有効化,無効化を設定します.
- `void ActiveTexture(TextureTargets const &target) const`\
テクスチャユニットをアクティブにします.
- `void Compile()`\
シェーダーをコンパイルします.シェーダーをコンパイルするためには最低でも頂点シェーダとフラグメントシェーダのソースコードが必要です.
- `void Use() const`\
シェーダーを使用します.この関数を実行する前に`Compile()`関数を実行してください.
- `void Unuse() const`\
シェーダーの使用を終了します.
- `static Str LoadShaderSource(Str const &path)`\
指定されたパスのファイルからシェーダのソースコードを読み込みます.

-----

# Skeleton関連のクラス
## 内容
- [Jointクラス](#Jointクラス)
- [Skeletonクラス](#Skeletonクラス)

## Jointクラス
このクラスはスケルトンのジョイントを管理します.ジョイントはボーンの情報を保持します.\
主なメンバ関数は以下の通りです.
- `Joint()`\
ジョイントを生成します.
- `Uint const &GetID() const`\
ジョイントのIDを取得します.
- `Shared<Joint> GetChild() const`\
ジョイントの子ジョイントを取得します.
- `Vec<Shared<Joint>> const &GetSiblings() const`\
ジョイントの兄弟ジョイントを取得します.
- `mat4 const &GetOffset() const`\
ジョイントのオフセット行列を取得します.
- `mat4 const &GetInitialTransform() const`\
ジョイントの初期変換行列を取得します.
- `mat4 const &GetTransform() const`\
ジョイントの変換行列を取得します.
- `void SetID(Uint const &id)`\
ジョイントのIDを設定します.
- `void SetChild(Shared<Joint> const &child)`\
ジョイントの子ジョイントを設定します.
- `void SetOffset(mat4 const &offset)`\
ジョイントのオフセット行列を設定します.
- `void SetInitialTransform(mat4 const &initialTransform)`\
ジョイントの初期変換行列を設定します.
- `void SetTransform(mat4 const &transform)`\
ジョイントの変換行列を設定します.ジョイントを操作する際はこの関数を利用してください.
- `void AddSibling(Shared<Joint> const &sibling)`\
ジョイントに兄弟ジョイントを追加します.
- `void Initialize(mat4 const &parentOffset)`\
ジョイントを初期化します.
- `void Transform(mat4 const &parentTransform,Vec<mat4> const &jointTransforms,Vec<mat4> &jointMatrices)`\
ジョイントの姿勢変換をします.この関数は`Skeleton`クラスから呼び出されます.

## Skeletonクラス
このクラスはスケルトンを管理します.スケルトンはジョイントの階層構造を保持します.\
主なメンバ関数は以下の通りです.
- `Skeleton()`\
スケルトンを生成します.
- `Shared<Joint> GetRoot() const`\
スケルトンのルートジョイントを取得します.
- `Vec<Shared<Joint>> const &GetJoints() const`\
スケルトンの全てのジョイントを取得します.
- `void SetRoot(Shared<Joint> const &root)`\
スケルトンのルートジョイントを設定します.
- `void SetJoints(Vec<Shared<Joint>> const &joints)`\
スケルトンの全てのジョイントを設定します.
- `void Initialize()`\
スケルトンを初期化します.
- `void ApplyTransforms(Vec<mat4> const &transforms)`\
スケルトンの姿勢変換をします.`transforms`の長さはジョイント数と一致する必要があります.\
この関数は`Animation`クラスから呼び出されます.また,この関数を呼び出す前に`Initialize()`関数を呼び出してください.

-----

# Text関連のクラス
## 内容
- [Textクラス](#Textクラス)

## Textクラス
- `Text()`\
テキストオブジェクトを生成します.
- `Text(Str const &text,Shared<Core::Font> const &font)`\
ASCII文字列とフォントからテキストオブジェクトを生成します.
- `Text(WStr const &text,Shared<Core::Font> const &font)`\
非ASCII文字を含む文字列とフォントからテキストオブジェクトを生成します.
- `void LoadShader(Str const &vertexPath,Str const &fragmentPath)`\
テキストを描画するシェーダーを設定します.
- `void LoadText(Str const &text,Shared<Core::Font> const &font)`\
描画するテキストとフォントを読み込みます.
- `void LoadText(WStr const &text,Shared<Core::Font> const &font)`\
描画する非ASCII文字を含む文字列とフォントを読み込みます.
- `void Render(Float const &x,Float const &y,Float const &windowWidth,Float const &windowHeight)`\
設定されたテキストを描画します.描画先のオブジェクトはこの関数が実行されたときに設定されている`Window`もしくは`Screen`になるため,描画先に指定したいオブジェクトがある場合はこの関数を実行する前に`Window::MakeCurrent()`関数もしくは,`Screen::Bind()`関数を実行し描画先を設定してください.

-----

# Texture関連のクラス
## 内容
- [FilterType列挙体](#FilterType列挙体)
- [WrappingType列挙体](#WrappingType列挙体)
- [CubeFace列挙体](#CubeFace列挙体)
- [TextureData構造体](#TextureData構造体)
- [Textureクラス](#Textureクラス)
- [CubeTextureクラス](#CubeTextureクラス)
- [テクスチャデータフォーマット](#テクスチャデータフォーマット)

## FilterType列挙体
この列挙体はテクスチャの拡大縮小時のフィルタリング方法を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `NEAREST` | 最近傍補間を行います |
| `LINEAR` | 線形補間を行います |
| `NEAREST_MIPMAP_NEAREST` | 最近傍補間を行い,ミップマップの最近傍補間を行います(この値は`minFilter`のみに適用可能です) |
| `LINEAR_MIPMAP_NEAREST` | 線形補間を行い,ミップマップの最近傍補間を行います(この値は`minFilter`のみに適用可能です) |
| `NEAREST_MIPMAP_LINEAR` | 最近傍補間を行い,ミップマップの線形補間を行います(この値は`minFilter`のみに適用可能です) |
| `LINEAR_MIPMAP_LINEAR` | 線形補間を行い,ミップマップの線形補間を行います(この値は`minFilter`のみに適用可能です) |

## WrappingType列挙体
この列挙体はテクスチャのラッピング方法(テクスチャの範囲外のUV座標が指定された場合の挙動)を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `REPEAT` | テクスチャの繰り返しを行います |
| `MIRRORED_REPEAT` | テクスチャの反転した繰り返しを行います |
| `CLAMP_TO_EDGE` | テクスチャの端の色でクランプします |
| `CLAMP_TO_BORDER` | テクスチャの端の色でクランプしますが,`borderColor`で指定された色でクランプします |

## CubeFace列挙体
この列挙体はキューブマップテクスチャの面を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `RIGHT` | X軸の正方向を示す面 |
| `LEFT` | X軸の負方向を示す面 |
| `TOP` | Y軸の正方向を示す面 |
| `BOTTOM` | Y軸の負方向を示す面 |
| `FRONT` | Z軸の正方向を示す面 |
| `BACK` | Z軸の負方向を示す面 |

## TextureData構造体
この構造体はテクスチャのデータを保持します.この構造体に対してプログラム上からフォーマットに従ったデータを設定することでプログラムからテクスチャを生成することができます.フォーマットの詳細は[テクスチャデータフォーマット](#テクスチャデータフォーマット)を参照してください.\
構造体のメンバは以下の通りです.
| メンバ | 用途 |
|:---:|-----|
| `data` | テクスチャのデータ |
| `width` | テクスチャの幅 |
| `height` | テクスチャの高さ |
| `channels` | テクスチャの色チャンネル数 |

## Textureクラス
このクラスは2Dテクスチャを管理します.\
主なメンバ関数は以下の通りです.
- `Texture()`\
空のテクスチャを生成します.
- `Texture(Uint const &texture,Uint const &width,Uint const &height,Uint const &channels)`\
OpenGLのバインドID,幅,高さ,色チャンネル数が指定された空のテクスチャを生成します.\
*この関数は[Screenクラス](#Screenクラス)からの呼び出し専用であり,ユーザーが直接呼び出すことは推奨されません.*
- `void SetFilter(FilterType const &filter)`\
テクスチャの拡大縮小時のフィルタリング方法を設定します.\
`FilterType`の詳細については[FilterType列挙体](#FilterType列挙体)を参照してください.
- `void SetWrapping(WrappingType const &wrap)`\
テクスチャのラッピング方法を設定します.\
`WrappingType`の詳細については[WrappingType列挙体](#WrappingType列挙体)を参照してください.
- `void LoadData(Uint width,Uint height,Uint channels,Ubyte const *data)`\
テクスチャのデータを読み込みます.
- `void LoadData(TextureData const &data)`\
テクスチャのデータを読み込みます.
- `void Bind() const`\
テクスチャをバインドします.
- `void Unbind() const`\
テクスチャのバインドを解除します.
- `static TextureData LoadTexture(Str const &path)`\
指定されたパスの画像ファイルからテクスチャのデータを読み込みます.

## CubeTextureクラス
このクラスはキューブマップテクスチャを管理します.\
主なメンバ関数は以下の通りです.
- `CubeTexture()`\
空のキューブマップテクスチャを生成します.
- `CubeTexture(Uint const &texture,Uint const &width,Uint const &height,Uint const &channels)`\
OpenGLのバインドID,幅,高さ,色チャンネル数が指定された空のキューブマップテクスチャを生成します.\
*この関数は[~~CubeScreenクラス~~](#CubeScreenクラス)からの呼び出し専用であり,ユーザーが直接呼び出すことは推奨されません.*
- `void SetFilter(FilterType const &filter)`\
テクスチャの拡大縮小時のフィルタリング方法を設定します.\
`FilterType`の詳細については[FilterType列挙体](#FilterType列挙体)を参照してください.
- `void SetWrapping(WrappingType const &wrap)`\
テクスチャのラッピング方法を設定します.
`WrappingType`の詳細については[WrappingType列挙体](#WrappingType列挙体)を参照してください.
- `void LoadData(CubeFace face,Uint width,Uint height,Uint channels,Ubyte const *data)`\
指定された面のテクスチャのデータを読み込みます.\
`CubeFace`の詳細については[CubeFace列挙体](#CubeFace列挙体)を参照してください.
- `void LoadData(CubeFace face,TextureData const &data)`\
指定された面のテクスチャのデータを読み込みます.\
`CubeFace`の詳細については[CubeFace列挙体](#CubeFace列挙体)を参照してください.
- `void LoadDatas(Vec<TextureData> const &datas)`\
全ての面のテクスチャのデータを[CubeFace列挙体](#CubeFace列挙体)の定義順に読み込みます.
- `void Bind() const`\
テクスチャをバインドします.
- `void Unbind() const`\
テクスチャのバインドを解除します.

## テクスチャデータフォーマット
テクスチャのデータは以下のフォーマットで設定する必要があります.ピクセルの順番は左上から右下に向かって並んでいる必要があります.
- 1チャンネルの場合\
`Ubyte`型の配列で各要素が0~255の値を取ります.`i`番目のピクセルデータの要素を`$r_{i}$`とすると次のような配列である必要があります.\
`$[r_{0},r_{1},r_{2},...,r_{n-1}]$`
- 2チャンネルの場合\
`Ubyte`型の配列で各要素が0~255の値を取ります.`i`番目のピクセルデータの要素を`$r_{i}$`,`$g_{i}$`とすると次のような配列である必要があります.\
`$[r_{0},g_{0},r_{1},g_{1},r_{2},g_{2},...,r_{n-1},g_{n-1}]$`
- 3チャンネルの場合\
`Ubyte`型の配列で各要素が0~255の値を取ります.`i`番目のピクセルデータの要素を`$r_{i}$`,`$g_{i}$`,`$b_{i}$`とすると次のような配列である必要があります.\
`$[r_{0},g_{0},b_{0},r_{1},g_{1},b_{1},r_{2},g_{2},b_{2},...,r_{n-1},g_{n-1},b_{n-1}]$`
- 4チャンネルの場合\
`Ubyte`型の配列で各要素が0~255の値を取ります.`i`番目のピクセルデータの要素を`$r_{i}$`,`$g_{i}$`,`$b_{i}$`,`$a_{i}$`とすると次のような配列である必要があります.\
`$[r_{0},g_{0},b_{0},a_{0},r_{1},g_{1},b_{1},a_{1},r_{2},g_{2},b_{2},a_{2},...,r_{n-1},g_{n-1},b_{n-1},a_{n-1}]$`

-----

# Window関連のクラス
## 内容
- [Modifier構造体](#Modifier構造体)
- [Key構造体](#Key構造体)
- [MousebuttonInput列挙体](#MousebuttonInput列挙体)
- [Keyboard列挙体](#Keyboard列挙体)
- [StandardCursor列挙体](#StandardCursor列挙体)
- [Iconクラス](#Iconクラス)
- [Cursorクラス](#Cursorクラス)
- [StandardCursorクラス](#StandardCursorクラス)
- [WindowSettings構造体](#WindowSettings構造体)
- [WindowPropertyクラス](#WindowPropertyクラス)
- [WindowControllerクラス](#WindowControllerクラス)
- [Windowクラス](#Windowクラス)

## Modifier構造体
この構造体は修飾キーの情報を保持します.\
構造体のメンバは以下の通りです.\
※ 押されている場合は`true`,押されていない場合は`false`が格納されます.
| メンバ | 説明 |
|:---:|-----|
| `shift` | シフトキーが押されているか |
| `control` | コントロールキーが押されているか |
| `alt` | Altキーが押されているか |
| `super` | スーパーキーが押されているか |
| `capsLock` | CapsLockキーが押されているか |
| `numLock` | NumLockキーが押されているか |

## Key構造体
この構造体はキーの情報を保持します.\
構造体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `key` | キーの種類 |
| `scancode` | キーのスキャンコード |
| `action` | キーのアクション |
| `modifier` | 修飾キーの情報 |

## MousebuttonInput列挙体
この列挙体はマウスボタンの入力を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `BUTTON1` | マウスボタン1(左クリック) |
| `BUTTON2` | マウスボタン2(右クリック) |
| `BUTTON3` | マウスボタン3(中クリック) |
| `BUTTON4` | マウスボタン4 |
| `BUTTON5` | マウスボタン5 |
| `BUTTON6` | マウスボタン6 |
| `BUTTON7` | マウスボタン7 |
| `BUTTON8` | マウスボタン8 |
| `LEFT_BUTTON` | 左クリック |
| `RIGHT_BUTTON` | 右クリック |
| `MIDDLE_BUTTON` | 中クリック |

## Keyboard列挙体
この列挙体はキーボードのキーを示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
- | `K_SPACE` | スペースキー |
- | `K_APOSTROPHE` | アポストロフィ |
- | `K_COMMA` | カンマ |
- | `K_MINUS` | マイナス |
- | `K_PERIOD` | ピリオド |
- | `K_SLASH` | スラッシュ |
- | `K_0` | 数字0 |
- | `K_1` | 数字1 |
- | `K_2` | 数字2 |
- | `K_3` | 数字3 |
- | `K_4` | 数字4 |
- | `K_5` | 数字5 |
- | `K_6` | 数字6 |
- | `K_7` | 数字7 |
- | `K_8` | 数字8 |
- | `K_9` | 数字9 |
- | `K_SEMICOLON` | セミコロン |
- | `K_EQUAL` | イコール |
- | `K_A` | Aキー |
- | `K_B` | Bキー |
- | `K_C` | Cキー |
- | `K_D` | Dキー |
- | `K_E` | Eキー |
- | `K_F` | Fキー |
- | `K_G` | Gキー |
- | `K_H` | Hキー |
- | `K_I` | Iキー |
- | `K_J` | Jキー |
- | `K_K` | Kキー |
- | `K_L` | Lキー |
- | `K_M` | Mキー |
- | `K_N` | Nキー |
- | `K_O` | Oキー |
- | `K_P` | Pキー |
- | `K_Q` | Qキー |
- | `K_R` | Rキー |
- | `K_S` | Sキー |
- | `K_T` | Tキー |
- | `K_U` | Uキー |
- | `K_V` | Vキー |
- | `K_W` | Wキー |
- | `K_X` | Xキー |
- | `K_Y` | Yキー |
- | `K_Z` | Zキー |
- | `K_LEFT_BRACKET` | 左角カッコ |
- | `K_BACKSLASH` | バックスラッシュ |
- | `K_RIGHT_BRACKET` | 右角カッコ |
- | `K_GRAVE_ACCENT` | バッククォート |
- | `K_WORLD_1` | `K_WORLD_1`(Non US) |
- | `K_WORLD_2` | `K_WORLD_2`(Non US) |
- | `K_ESCAPE` | エスケープキー |
- | `K_ENTER` | エンターキー |
- | `K_TAB` | タブキー |
- | `K_BACKSPACE` | バックスペースキー |
- | `K_INSERT` | インサートキー |
- | `K_DELETE` | デリートキー |
- | `K_RIGHT` | 右矢印キー |
- | `K_LEFT` | 左矢印キー |
- | `K_DOWN` | 下矢印キー |
- | `K_UP` | 上矢印キー |
- | `K_PAGE_UP` | ページアップキー |
- | `K_PAGE_DOWN` | ページダウンキー |
- | `K_HOME` | ホームキー |
- | `K_END` | エンドキー |
- | `K_CAPS_LOCK` | CapsLockキー |
- | `K_SCROLL_LOCK` | ScrollLockキー |
- | `K_NUM_LOCK` | NumLockキー |
- | `K_PRINT_SCREEN` | PrintScreenキー |
- | `K_PAUSE` | Pauseキー |
- | `K_F1` | F1キー |
- | `K_F2` | F2キー |
- | `K_F3` | F3キー |
- | `K_F4` | F4キー |
- | `K_F5` | F5キー |
- | `K_F6` | F6キー |
- | `K_F7` | F7キー |
- | `K_F8` | F8キー |
- | `K_F9` | F9キー |
- | `K_F10` | F10キー |
- | `K_F11` | F11キー |
- | `K_F12` | F12キー |
- | `K_F13` | F13キー |
- | `K_F14` | F14キー |
- | `K_F15` | F15キー |
- | `K_F16` | F16キー |
- | `K_F17` | F17キー |
- | `K_F18` | F18キー |
- | `K_F19` | F19キー |
- | `K_F20` | F20キー |
- | `K_F21` | F21キー |
- | `K_F22` | F22キー |
- | `K_F23` | F23キー |
- | `K_F24` | F24キー |
- | `K_F25` | F25キー |
- | `K_KP_0` | テンキーの0 |
- | `K_KP_1` | テンキーの1 |
- | `K_KP_2` | テンキーの2 |
- | `K_KP_3` | テンキーの3 |
- | `K_KP_4` | テンキーの4 |
- | `K_KP_5` | テンキーの5 |
- | `K_KP_6` | テンキーの6 |
- | `K_KP_7` | テンキーの7 |
- | `K_KP_8` | テンキーの8 |
- | `K_KP_9` | テンキーの9 |
- | `K_KP_DECIMAL` | テンキーの小数点 |
- | `K_KP_DIVIDE` | テンキーの割り算 |
- | `K_KP_MULTIPLY` | テンキーの掛け算 |
- | `K_KP_SUBTRACT` | テンキーの引き算 |
- | `K_KP_ADD` | テンキーの足し算 |
- | `K_KP_ENTER` | テンキーのエンターキー |
- | `K_KP_EQUAL` | テンキーのイコールキー |
- | `K_LEFT_SHIFT` | 左シフトキー |
- | `K_LEFT_CONTROL` | 左コントロールキー |
- | `K_LEFT_ALT` | 左Altキー |
- | `K_LEFT_SUPER` | 左スーパーキー |
- | `K_RIGHT_SHIFT` | 右シフトキー |
- | `K_RIGHT_CONTROL` | 右コントロールキー |
- | `K_RIGHT_ALT` | 右Altキー |
- | `K_RIGHT_SUPER` | 右スーパーキー |
- | `K_MENU` | メニューキー |
- | `K_LAST` | 最後のキー |

## StandardCursor列挙体
この列挙体は標準のカーソルの種類を示すための列挙体です.\
列挙体のメンバは以下の通りです.
| メンバ | 説明 |
|:---:|-----|
| `ARROW` | 矢印カーソル |
| `IBEAM` | Iビームカーソル |
| `CROSSHAIR` | 十字カーソル |
| `HAND` | 手カーソル |
| `HRESIZE` | 水平リサイズカーソル |
| `VRESIZE` | 垂直リサイズカーソル |


## Iconクラス
このクラスはウィンドウのアイコンを管理します.アイコンの画像の読み込みはこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Icon()`\
アイコンを生成します.
- `size_t GetSize() const`\
アイコンの数を取得します.
- `void AddImage(Uint const &width,Uint const &height,Ubyte const *pixels)`\
アイコンに画像を追加します.`Texture::LoadData()`関数で読み込んだ画像データを設定するか,[テクスチャデータフォーマット](#テクスチャデータフォーマット)に従ったデータを設定してください.

## Cursorクラス
このクラスはカーソルを管理します.独自の外観を持つカーソルの作成及び描画はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Cursor(int const &xHot = 0,int const &yHot = 0)`\
カーソルを生成します.カーソルのホットスポットの座標を指定することができます.
- `void SetImage(Uint const &width,Uint const &height,Ubyte const *pixels)`\
カーソルの画像を設定します.`Texture::LoadData()`関数で読み込んだ画像データを設定するか,[テクスチャデータフォーマット](#テクスチャデータフォーマット)に従ったデータを設定してください.

## StandardCursorクラス
このクラスは標準のカーソルを管理します.標準のカーソルの作成及び描画はこのクラスのメンバ関数を利用して行ってください.標準のカーソルの種類は[StandardCursor列挙体](#StandardCursor列挙体)を参照してください.\
主なメンバ関数は以下の通りです.
- `StandardCursor(CursorShape const &shape)`\
標準のカーソルを生成します.カーソルの種類は`shape`で指定します.

## WindowSettings構造体
この構造体はウィンドウの設定を保持します.この構造体のメンバは全て`public`であり,この構造体のメンバを書き換えた上で`Window`クラスに渡すことでウィンドウの設定を変更できます.
それぞれのメンバの詳細は以下の通りです.
| メンバ | 用途 | デフォルト値 |
|:---:|-----|:---:|
| `resizable` | 画面のサイズが変更可能かを設定します | `GLFW_TRUE` |
| `visible` | 画面の表示/非表示を設定します | `GLFW_TRUE` |
| `decorated` | 画面上部のボタン等を付けるかどうかを設定します | `GLFW_TRUE` |
| `focused` | 画面が非最大化されて生成されたときに入力フォーカスが与えられるかどうかを設定します | `GLFW_TRUE` |
| `autoIconify` | 画面が入力フォーカスを失ったときに全画面化が自動的に解除され,アイコン化されるかを設定します | `GLFW_TRUE` |
| `floating` | 画面が常に最前面に表示されるかを設定します | `GLFW_FALSE` |
| `maximized` | 画面が生成時に最大化されるかを設定します | `GLFW_FALSE` |
| `centerCursor` | 全画面生成時にカーソルを中央に配置するかを設定します | `GLFW_TRUE` |
| `transparentFramebuffer` | 画面のフレームバッファが透明かどうかを設定します | `GLFW_FALSE` |
| `focusOnShow` | `Window::Show()`が呼び出されたときに画面に入力フォーカスをあてるかを設定します | `GLFW_TRUE` |
| `scaleToMonitor` | 画面のコンテンツ領域を,それが配置されているモニターのコンテンツスケールに基づいてサイズ変更するかどうかを設定します | `GLFW_FALSE` |

## WindowPropertyクラス
このクラスはウィンドウのプロパティを管理します.ウィンドウのプロパティの取得はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Str const &GetTitle() const`\
ウィンドウのタイトルを取得します.
- `Pair<double> const &GetScrollOffset() const`\
スクロールのオフセットを取得します.
- `Vec<Uint> const &GetCodePoints() const`\
入力された文字のコードポイントを取得します.入力された文字情報はUnicodeのコードポイントで取得されます.\
また,記録された文字情報は`Window::ClearInputs()`関数もしくは`WindowProperty::ClearInputs()`を呼び出すまで保持されます.
- `Vec<Key> const &GetKeys() const`\
入力されたキーを取得します.入力されたキー情報は`Key`列挙体のメンバで取得されます.\
また,記録されたキー情報は`Window::ClearInputs()`関数もしくは`WindowProperty::ClearInputs()`を呼び出すまで保持されます.
- `Vec<Str> const &GetDroppedFiles() const`\
ドロップされたファイルのパスを取得します.\
また,記録されたファイルパスは`Window::ClearInputs()`関数もしくは`WindowProperty::ClearInputs()`を呼び出すまで保持されます.
- `Pair<Uint> const &GetSize() const`\
ウィンドウのサイズを取得します.
- `Pair<Uint> const &GetPosition() const`\
ウィンドウの位置を取得します.
- `Pair<double> const &GetCursorPosition() const`\
カーソルの位置を取得します.
- `void ClearInputs()`\
入力情報をクリアします.

## WindowControllerクラス
このクラスはウィンドウの各種コールバック関数及び毎フレームの処理を行う関数を管理します.ウィンドウのコールバック関数及び毎フレームの処理はこのクラスを継承し実装することで行ってください.`OnFrame()`関数は必ずオーバーライドしてください.他のコールバックはデフォルトでは何も行いません.\
オーバーライド可能なコールバック関数は以下の通りです.
- `virtual void PositionCallback(int const &xpos,int const &ypos)`\
ウィンドウの位置が変更されたときに呼び出されます.
- `virtual void SizeCallback(int const &width,int const &height)`\
ウィンドウのサイズが変更されたときに呼び出されます.
- `virtual void CloseCallback()`\
ウィンドウが閉じられたときに呼び出されます.
- `virtual void RefreshCallback()`\
ウィンドウが再描画されるときに呼び出されます.
- `virtual void FocusCallback(Bool const &focused)`\
ウィンドウがフォーカスを得た/失ったときに呼び出されます.
- `virtual void IconifyCallback(Bool const &iconified)`\
ウィンドウがアイコン化された/解除されたときに呼び出されます.
- `virtual void MaximizeCallback(Bool const &maximized)`\
ウィンドウが最大化された/解除されたときに呼び出されます.
- `virtual void FramebufferSizeCallback(int const &width,int const &height)`\
ウィンドウのフレームバッファのサイズが変更されたときに呼び出されます.
- `virtual void ContentScaleCallback(float const &xscale,float const &yscale)`\
ウィンドウのコンテンツスケールが変更されたときに呼び出されます.
- `virtual void MousebuttonCallback(Uint const &button,Uint const &action,Modifier const &mods)`\
マウスボタンが押された/離されたときに呼び出されます.
- `virtual void CursorPositionCallback(double const &xpos,double const &ypos)`\
カーソルの位置が変更されたときに呼び出されます.
- `virtual void CursorEnterCallback(Bool const &entered)`\
カーソルがウィンドウ内に入った/出たときに呼び出されます.
- `virtual void ScrollCallback(double const &xoffset,double const &yoffset)`\
スクロールが行われたときに呼び出されます.
- `virtual void KeyCallback(Key const &key)`\
キーが押された/離されたときに呼び出されます.
- `virtual void CharCallback(Uint const &codepoint)`\
文字が入力されたときに呼び出されます.
- `virtual void DropCallback(Vec<Str> const &paths)`\
ファイルがドロップされたときに呼び出されます.
- `virtual void OnFrame(Window *window)`\
*毎フレームの処理を行います.必ずオーバーライドしてください.*

## Windowクラス
このクラスはウィンドウを管理します.ウィンドウの作成及び描画はこのクラスのメンバ関数を利用して行ってください.また,ウィンドウの設定は`WindowSettings`構造体を利用して行ってください.ウィンドウに対する操作等もこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Window(Uint const &width,Uint const &height,Str const &title,WindowSettings const &settings)`\
ウィンドウを生成します.ウィンドウの幅,高さ,タイトル,設定を指定してください.
- `Pair<int> GetSize() const`\
ウィンドウのサイズを取得します.
- `Pair<int> GetPosition() const`\
ウィンドウの位置を取得します.
- `Pair<double> GetCursorPosition() const`\
カーソルの位置を取得します.
- `Pair<double> GetScrollOffset() const`\
スクロールのオフセットを取得します.
- `Str GetClipboardString() const`\
クリップボードに格納された文字列を取得します.
- `Str GetTitle() const`\
ウィンドウのタイトルを取得します.
- `Vec<Uint> const &GetCodePoints() const`\
ウィンドウに入力された文字のコードポイントを取得します.
- `Vec<Key> const &GetKeys() const`\
ウィンドウに入力されたキーを取得します.
- `Vec<Str> const &GetDroppedFiles() const`\
ウィンドウにドロップされたファイルのパスを取得します.
- `float GetOpacity() const`\
ウィンドウの透明度を取得します.
- `Bool GetMousebutton(MousebuttonInput const &button) const`\
指定されたマウスボタンが押されているかを取得します.\
`MousebuttonInput`の詳細については[MousebuttonInput列挙体](#MousebuttonInput列挙体)を参照してください.
- `int GetInputMode(InputType const &type) const`\
指定された入力モードの値を取得します.
- `template <typename T> T *GetUserPointer() const`\
ユーザーポインタを取得します.テンプレート引数にはユーザーポインタの型を指定してください.
- `void SetCurrentContext() const`\
ウィンドウをカレントコンテキスト(描画操作対象)に設定します.
- `void SetIcon(Icon const &icon)`\
ウィンドウのアイコンを設定します.アイコンの画像は`Icon`クラスのメンバ関数を利用して設定してください.
- `void SetCursor(Cursor const &cursor)`\
ウィンドウのカーソルを設定します.カーソルの画像は`Cursor`クラスのメンバ関数を利用して設定してください.
- `void SetCursor(StandardCursor const &cursor)`\
ウィンドウのカーソルを標準のカーソルに設定します.カーソルの種類は`StandardCursor`クラスのメンバ関数を利用して設定してください.
- `void SetDefaultCursor()`\
ウィンドウのカーソルをデフォルトのカーソルに設定します.
- `void SetSize(Pair<int> const &size)`\
ウィンドウのサイズを設定します.
- `void SetPosition(Pair<int> const &position)`\
ウィンドウの位置を設定します.
- `void SetCursorPosition(Pair<int> const &position)`\
カーソルの位置を設定します.
- `void SetClipboardString(Str const &string)`\
クリップボードに文字列を設定します.
- `void SetTitle(Str const &title)`\
ウィンドウのタイトルを設定します.
- `void SetOpacity(float const &opacity)`\
ウィンドウの透明度を設定します.
- `void SetInputMode(InputType const &type,int const &value)`\
指定された入力モードの値を設定します.
- `template <typename T> void SetUserPointer(T *pointer)`\
ユーザーポインタを設定します.テンプレート引数は自動的に型が推論されます.
- `void SetWindowController(WindowController *callbacks)`\
ウィンドウのコールバック関数を設定します.コールバック関数は`WindowController`クラスを継承し実装してください.
- `Bool IsClosed() const`\
ウィンドウが閉じられたかを取得します.
- `Bool IsFullScreen() const`\
ウィンドウが全画面表示されているかを取得します.
- `Bool IsWindowed() const`\
ウィンドウがウィンドウモードで表示されているかを取得します.
- `Bool IsIconified() const`\
ウィンドウがアイコン化されているかを取得します.
- `Bool IsMaximized() const`\
ウィンドウが最大化されているかを取得します.
- `Bool IsVisible() const`\
ウィンドウが表示されているかを取得します.
- `Bool IsFocused() const`\
ウィンドウがフォーカスを得ているかを取得します.
- `Bool IsTransparent() const`\
ウィンドウのフレームバッファが透明かを取得します.
- `Bool IsDecorated() const`\
ウィンドウ上部にボタン等が付いているかを取得します.
- `Bool IsResizable() const`\
ウィンドウのサイズが変更可能かを取得します.
- `Bool IsFloating() const`\
ウィンドウが常に最前面に表示されるかを取得します.
- `Bool IsAutoIconified() const`\
ウィンドウが入力フォーカスを失ったときに全画面化が自動的に解除され,アイコン化されるかを取得します.
- `Bool IsFocusOnShowed() const`\
`Window::Show()`が呼び出されたときに画面に入力フォーカスをあてるかを取得します.
- `Bool IsPressing(Keyboard const &key) const`\
指定されたキーが押されているかを取得します.
- `Bool IsEntering() const`\
カーソルがウィンドウ内に入ったかを取得します.
- `void Close()`\
ウィンドウを閉じます.
- `void Iconify() const`\
ウィンドウをアイコン化します.
- `void Maximize() const`\
ウィンドウを最大化します.
- `void Show() const`\
ウィンドウを表示します.
- `void Hide() const`\
ウィンドウを非表示にします.
- `void Focus() const`\
ウィンドウに入力フォーカスを与えます.
- `void Restore() const`\
ウィンドウを元の状態に戻します.
- `void RequestAttention() const`\
ウィンドウに注意を要求します.
- `void Fill(Vec<float> const &color) const`\
ウィンドウを指定された色で塗りつぶします.色は`[R,G,B,A]`の形式で`0.0~1.0`の範囲で指定してください.
- `void Clear() const`\
ウィンドウをクリアします.
- `void ClearColor() const`\
ウィンドウのカラーバッファをクリアします.
- `void ClearDepth() const`\
ウィンドウのデプスバッファをクリアします.
- `void ClearStencil() const`\
ウィンドウのステンシルバッファをクリアします.
- `void Swap() const`\
ウィンドウのバッファを入れ替えます.
- `void PollEvents() const`\
ウィンドウに対するイベントを処理します.
- `void Bind() const`\
ウィンドウをカレントコンテキスト(描画操作対象)に設定します.
- `void Frame()`\
ウィンドウのフレームを描画します.

-----

# Math関連のクラス
## 内容
- [Complexクラス](#Complexクラス)
- [Fractionクラス](#Fractionクラス)
- [MatrixBaseクラス](#MatrixBaseクラス)
- [Quaternionクラス](#Quaternionクラス)
- [Utility関数](#Utility関数)

## Complexクラス
このクラスは複素数を表します.複素数の演算はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Complex()`\
実部,虚部がともに0の複素数を生成します.
- `Complex(T real,T imaginary)`\
実部,虚部を指定して複素数を生成します.
- `Complex(Complex<T> const &other)`\
他の複素数をコピーして複素数を生成します.
- `Complex(Complex<T> &&other)`\
他の複素数をムーブして複素数を生成します.
- `Complex(Complex<U> const &other)`\
他の型の複素数をコピーして複素数を生成します.
- `Complex(Complex<U> &&other)`\
他の型の複素数をムーブして複素数を生成します.
- `T const &GetReal() const`\
実部を取得します.
- `T const &GetImaginary() const`\
虚部を取得します.
- `T AcquireLength() const`\
複素数の絶対値を取得します.
- `T AcquireArg() const`\
複素数の偏角を取得します.

## Fractionクラス
このクラスは分数を表します.分数の演算はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `Fraction()`\
分子が0,分母が1の分数を生成します.
- `Fraction(T const &numerator)`\
分子を指定して分数を生成します.
- `Fraction(T const &numerator,T const &denominator)`\
分子,分母を指定して分数を生成します.
- `Fraction(Fraction<T> const &other)`\
他の分数をコピーして分数を生成します.
- `Fraction(Fraction<T> &&other) noexcept`\
他の分数をムーブして分数を生成します.
- `T const &GetNumerator() const`\
分子を取得します.
- `T const &GetDenominator() const`\
分母を取得します.
- `Fraction<T> &SetNumerator(T const &numerator)`\
分子を設定します.
- `Fraction<T> &SetDenominator(T const &denominator)`\
分母を設定します.

## MatrixBaseクラス
このクラスは行列を表します.行列の演算はこのクラスのメンバ関数を利用して行ってください.\
主なメンバ関数は以下の通りです.
- `MatrixBase()`

- `MatrixBase(Uint const &row,Uint const &column)`
- `MatrixBase(Uint const &row,Uint const &column,T const *array)`
- `MatrixBase(Uint const &row,Uint const &column,T const &value)`
- `MatrixBase(Uint const &row,Uint const &column,Vec<T> const &value)`
- `MatrixBase(Vec<Vec<T>> const &value)`
- `MatrixBase(MatrixBase<T> const &other)`
- `MatrixBase(MatrixBase<T> &&other)`
- `MatrixBase(Uint const &row,Uint const &column,U const *array)`
- `MatrixBase(Uint const &row,Uint const &column,U const &value)`
- `MatrixBase(Uint const &row,Uint const &column,Vec<U> const &value)`
- `MatrixBase(Vec<Vec<U>> const &value)`
- `MatrixBase(MatrixBase<U> const &other)`
- `Uint GetSize() const`
- `Uint GetRow() const`
- `Uint GetColumn() const`
- `T *GetArray()`
- `T const *GetArray() const`
- `MatrixBase<T> GetCopy() const`
- `Uint AcquireMaxDigit() const`
- `T AcquireMaxValue() const`
- `T AcquireMinValue() const`
- `Uint AcquireRank() const`
- `T AcquireDeterminant() const`
- `MatrixBase<T> AcquireRow(Uint const &row) const`
- `MatrixBase<T> AcquireColumn(Uint const &column) const`
- `MatrixBase<T> AcquireCofactor(Uint const &row,Uint const &column) const`
- `MatrixBase<T> AcquireTransposed() const`
- `MatrixBase<T> AcquireUpperTriangular(int *c = nullptr) const`
- `MatrixBase<T> AcquireInversed() const`
- `void SetRow(Uint const &row,T const *value)`
- `void SetRow(Uint const &row,Vec<T> const &value)`
- `void SetRow(Uint const &row,MatrixBase<T> const &value)`
- `void SetColumn(Uint const &column,T const *value)`
- `void SetColumn(Uint const &column,Vec<T> const &value)`
- `void SetColumn(Uint const &column,MatrixBase<T> const &value)`
- `Uint SearchNonZeroRow(Uint const &row,Uint const &start = 0) const`
- `Uint SearchNonZeroColumn(Uint const &column,Uint const &start = 0) const`
- `void SwapRow(Uint const &row1,Uint const &row2)`
- `void SwapColumn(Uint const &column1,Uint const &column2)`
- `void MultiplyRow(Uint const &row,T const &value)`
- `void MultiplyColumn(Uint const &column,T const &value)`
- `void AddRow(Uint const &row1,Uint const &row2,T const &value)`
- `void AddColumn(Uint const &column1,Uint const &column2,T const &value)`
- `void LU(MatrixBase<T> &L,MatrixBase<T> &U) const`
- `void Transpose()`
- `void UpperTriangulate(int *c = nullptr)`
- `void Inverse()`

-----
