Imports System.Runtime.InteropServices
Imports System.Threading
Imports System.Text
Imports System.Linq

Public Class ScrollCapture

#Region "WinAPI 定義"
    ' WinAPI 関数の定義
    <DllImport("user32.dll")>
    Private Shared Function SetForegroundWindow(hWnd As IntPtr) As Boolean
    End Function

    <DllImport("user32.dll", CharSet:=CharSet.Auto)>
    Private Shared Function SendMessage(hWnd As IntPtr, msg As UInteger, wParam As IntPtr, lParam As IntPtr) As IntPtr
    End Function

    <DllImport("user32.dll")>
    Private Shared Function GetWindowRect(hWnd As IntPtr, ByRef lpRect As RECT) As Boolean
    End Function

    <DllImport("user32.dll", CharSet:=CharSet.Auto)>
    Private Shared Function EnumChildWindows(hWndParent As IntPtr, lpEnumFunc As EnumWindowsProc, lParam As IntPtr) As Boolean
    End Function

    <DllImport("user32.dll", CharSet:=CharSet.Auto)>
    Private Shared Function GetClassName(hWnd As IntPtr, lpClassName As StringBuilder, nMaxCount As Integer) As Integer
    End Function

    ' 定数定義
    Private Const WM_VSCROLL As UInteger = &H115
    Private Const SB_PAGEDOWN As UInteger = 3
    Private Const SB_TOP As UInteger = 6

    ' RECT 構造体
    <StructLayout(LayoutKind.Sequential)>
    Private Structure RECT
        Public Left As Integer
        Public Top As Integer
        Public Right As Integer
        Public Bottom As Integer
    End Structure

    Private Delegate Function EnumWindowsProc(hWnd As IntPtr, lParam As IntPtr) As Boolean
#End Region

    ''' <summary>
    ''' スクロールしながらブラウザ画面をキャプチャし、結合する
    ''' </summary>
    ''' <returns>結合されたビットマップ</returns>
    Public Shared Function CaptureAndCombine() As Bitmap

        ' アクティブなブラウザウィンドウを取得
        Dim hParent As IntPtr = BrowserWindowDetector.IsForegroundWindowBrowser()
        If hParent = IntPtr.Zero Then Return Nothing

        ' Internet Explorer_Server ウィンドウを検索
        Dim hWndIE As IntPtr = FindIEWindow(hParent)
        If hWndIE = IntPtr.Zero Then Return Nothing

        ' ウィンドウを前面に移動
        SetForegroundWindow(hWndIE)
        Thread.Sleep(100)

        ' スクロールを最上部に設定
        SendMessage(hWndIE, WM_VSCROLL, CType(SB_TOP, IntPtr), IntPtr.Zero)
        Thread.Sleep(100)

        ' キャプチャした画像を保存するリスト
        Dim capturedImages As New List(Of Bitmap)
        Dim previousBitmap As Bitmap = Nothing

        ' スクロールしながらキャプチャ
        For i As Integer = 1 To 20 ' 最大20ページ分をキャプチャ
            Dim currentBitmap As Bitmap = CaptureBitmap(hParent)
            If currentBitmap Is Nothing Then Exit For

            ' 前回の画像と比較し、同じなら終了
            If previousBitmap IsNot Nothing AndAlso CompareBitmaps(previousBitmap, currentBitmap) Then
                currentBitmap.Dispose()
                Exit For
            End If

            ' 前回の画像を解放し、新しい画像を保持
            previousBitmap?.Dispose()
            previousBitmap = currentBitmap
            capturedImages.Add(New Bitmap(currentBitmap))

            ' PageDown を送信
            SendMessage(hWndIE, WM_VSCROLL, CType(SB_PAGEDOWN, IntPtr), IntPtr.Zero)
            Thread.Sleep(100)
        Next

        ' スクロールを最上部に戻す
        SendMessage(hWndIE, WM_VSCROLL, CType(SB_TOP, IntPtr), IntPtr.Zero)

        ' 画像を結合
        Dim combinedImage As Bitmap = CombineImagesVertically(capturedImages)

        ' 個々の画像を解放
        For Each img In capturedImages
            img.Dispose()
        Next

        Return combinedImage
    End Function

    ''' <summary>
    ''' 指定ウィンドウのスクリーンショットを取得
    ''' </summary>
    Private Shared Function CaptureBitmap(hWnd As IntPtr) As Bitmap
        Dim rect As Rectangle = GetWindowRectEx(hWnd)
        If rect.Width = 0 Or rect.Height = 0 Then
            Return Nothing
        End If

        Dim bmp As New Bitmap(rect.Width, rect.Height)
        Using g As Graphics = Graphics.FromImage(bmp)
            g.CopyFromScreen(New Point(rect.Left, rect.Top), New Point(0, 0), rect.Size)
        End Using

        Return bmp

    End Function

    ''' <summary>
    ''' 2つのビットマップを比較
    ''' </summary>
    Private Shared Function CompareBitmaps(bmp1 As Bitmap, bmp2 As Bitmap) As Boolean

        If bmp1.Size <> bmp2.Size Then
            Return False
        End If

        Dim nDiffCount As Integer = 0

        For y As Integer = 0 To bmp1.Height - 1 Step 10
            For x As Integer = 0 To bmp1.Width - 1 Step 10
                If bmp1.GetPixel(x, y) <> bmp2.GetPixel(x, y) Then
                    nDiffCount += 1
                    If nDiffCount >= 10 Then
                        Return False
                    End If
                End If
            Next
        Next

        Return True

    End Function

    ''' <summary>
    ''' 画像を縦に結合
    ''' </summary>
    Private Shared Function CombineImagesVertically(images As List(Of Bitmap)) As Bitmap
        If images.Count = 0 Then
            Return Nothing
        End If

        Dim totalWidth As Integer = images.Max(Function(img) img.Width)
        Dim totalHeight As Integer = images.Sum(Function(img) img.Height)

        Dim finalImage As New Bitmap(totalWidth, totalHeight)
        Using g As Graphics = Graphics.FromImage(finalImage)
            Dim currentY As Integer = 0
            For Each img In images
                g.DrawImage(img, 0, currentY)
                currentY += img.Height
            Next
        End Using
        Return finalImage
    End Function

    ''' <summary>
    ''' 指定ウィンドウの座標を取得
    ''' </summary>
    Private Shared Function GetWindowRectEx(hWnd As IntPtr) As Rectangle
        Dim rect As New RECT()
        If GetWindowRect(hWnd, rect) Then
            Return New Rectangle(rect.Left, rect.Top, rect.Right - rect.Left, rect.Bottom - rect.Top)
        End If
        Return Rectangle.Empty
    End Function

    ''' <summary>
    ''' EdgeからIEモードのウィンドウを検索
    ''' </summary>
    Private Shared Function FindIEWindow(parentHwnd As IntPtr) As IntPtr
        Dim result As IntPtr = IntPtr.Zero
        EnumChildWindows(parentHwnd, Function(hWnd, lParam)
                                         Dim className As New StringBuilder(256)
                                         GetClassName(hWnd, className, className.Capacity)
                                         If className.ToString() = "Internet Explorer_Server" Then
                                             result = hWnd
                                             Return False ' 発見したら停止
                                         End If
                                         Return True
                                     End Function, IntPtr.Zero)
        Return result
    End Function

End Class
