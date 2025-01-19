Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Linq
Imports System.Text
Imports System.Windows.Forms

Public Class WebBrowserEx
    Inherits System.Windows.Forms.WebBrowser

#Region "プロパティ"
    ' プロパティ: 要素への自動スクロールを有効または無効にする
    Property AutoScrollToElement As Boolean = True
#End Region

#Region "テキストボックス設定"
    ' 指定されたIDの要素にテキストを設定
    Public Sub SetTextById(ByVal sId As String, ByVal sText As String)
        GetElementById(sId).SetAttribute("value", sText)
    End Sub

    ' 指定された名前の要素にテキストを設定
    Public Sub SetTextByName(ByVal sName As String, ByVal sText As String)
        GetElementByName(sName).SetAttribute("value", sText)
    End Sub
#End Region

#Region "テキストボックス取得"
    ' 指定されたIDの要素のテキストを取得
    Public Function GetTextById(ByVal sId As String)
        Return If(TryCast(GetElementById(sId), HtmlElement)?.GetAttribute("value"), "")
    End Function

    ' 指定された名前の要素のテキストを取得
    Public Function GetTextByName(ByVal sName As String) As String
        Return If(TryCast(GetElementByName(sName), HtmlElement)?.GetAttribute("value"), "")
    End Function
#End Region

#Region "ボタンクリック"
    ' 指定されたIDのボタンをクリック
    Public Sub ClickButtonById(sId As String)
        GetElementById(sId).InvokeMember("click")
    End Sub

    ' 指定された名前のボタンをクリック
    Public Sub ClickButtonByName(sName As String)
        GetElementByName(sName).InvokeMember("click")
    End Sub

    ' 指定されたテキストのボタンをクリック
    Public Sub ClickButtonByText(sText As String)
        Dim elements As HtmlElementCollection = Document.GetElementsByTagName("button")
        For Each element As HtmlElement In elements
            If element.GetAttribute("value") = sText Then
                SelectElement(element)
                element.InvokeMember("click")
            End If
        Next
    End Sub
#End Region

#Region "コンボボックス選択"
    ' 指定された名前のコンボボックスに値を設定 (インデックス指定)
    Public Sub SelectByNameAndIndex(sName As String, index As Integer)
        GetElementByName(sName).SetAttribute("SelectedIndex", index.ToString())
    End Sub

    ' 指定されたIDのコンボボックスに値を設定 (インデックス指定)
    Public Sub SelectByIdAndIndex(sId As String, index As Integer)
        GetElementById(sId).SetAttribute("SelectedIndex", index.ToString())
    End Sub

    ' 指定された名前のコンボボックスに値を設定 (テキスト指定)
    Public Sub SelectByNameAndText(sName As String, sText As String)
        SelectByText(GetElementByName(sName), sText)
    End Sub

    ' 指定されたIDのコンボボックスに値を設定 (テキスト指定)
    Public Sub SelectByIdAndText(sId As String, sText As String)
        SelectByText(GetElementById(sId), sText)
    End Sub
#End Region

#Region "チェックボックス チェック"
    ' 指定された名前のチェックボックスを設定
    Public Function SetCheckByName(ByVal sName As String, ByVal bCheck As Boolean) As Boolean
        Try
            GetElementByName(sName).SetAttribute("checked", If(bCheck, "true", Nothing))
            Return True
        Catch
            Return False
        End Try
    End Function

    ' 指定されたIDのチェックボックスを設定
    Public Function SetCheckById(ByVal sId As String, ByVal bCheck As Boolean) As Boolean
        Try
            GetElementById(sId).SetAttribute("checked", If(bCheck, "true", Nothing))
            Return True
        Catch
            Return False
        End Try
    End Function

    Public Function SetCheckByText(sText As String, ByVal bCheck As Boolean) As Boolean

        ' ----------------------------------------------------------------------------------------------
        ' うまくいかなかったのでボツ。
        ' チェックボックスの定義はこんな漢字で、テキストはlabelに設定されている？取得不可？
        ' " <label><input type="checkbox" id="checkbox1" name="chk_one"> チェックボックス 1</label>"
        ' ----------------------------------------------------------------------------------------------
        Debug.Assert(False)

        Dim elements As HtmlElementCollection = Document.GetElementsByTagName("input")

        For Each element As HtmlElement In elements
            If element.GetAttribute("type").ToLower() = "checkbox" Then
                If element.OuterText = sText OrElse element.InnerText = sText Then
                    SelectElement(element)
                    element.SetAttribute("checked", If(bCheck, "true", Nothing))
                    Return True
                End If
            End If
        Next
        Return False
    End Function
#End Region

#Region "ラジオボタン チェック"
    ' 指定されたIDのラジオボタンをチェック
    Public Function ClickRadioById(ByVal sName As String, Optional ByVal bCheck As Boolean = True) As Boolean
        Return SetCheckById(sName, bCheck)
    End Function

    ' 指定された名前とテキストのラジオボタンをチェック
    Public Function ClickRadioByNameAndText(ByVal sName As String, ByVal sText As String, Optional ByVal bCheck As Boolean = True) As Boolean
        Dim elements As HtmlElementCollection = Me.Document.GetElementsByTagName("input")
        For Each element As HtmlElement In elements
            If element.GetAttribute("name") = sName AndAlso element.GetAttribute("type").ToLower() = "radio" Then
                Debug.Print(element.GetAttribute("value"))
                If element.GetAttribute("value") = sText Then
                    SelectElement(element)
                    element.SetAttribute("checked", "true")
                    Return True
                End If
            End If
        Next
        Return False
    End Function
#End Region

    Private Function SelectElement(ByRef element As HtmlElement) As HtmlElement
        If element Is Nothing Then
            Debug.Assert(False)
            Return Nothing
        Else
            element.Focus()
            ScrollToElement(element)
            Return element
        End If
    End Function

#Region "ローカルメソッド"
    ' 指定された名前で要素を取得し、フォーカスを設定してスクロールする
    Private Function GetElementByName(ByVal sName As String) As HtmlElement
        Return SelectElement(Document.All(sName))
    End Function

    ' 指定されたIDで要素を取得し、フォーカスを設定してスクロールする
    Private Function GetElementById(ByVal sId As String) As HtmlElement
        Return SelectElement(Document.GetElementById(sId))
    End Function

    ' 指定されたテキストを含む要素を選択状態にする
    Private Sub SelectByText(ByRef element As HtmlElement, sText As String)
        For i As Integer = 0 To element.All.Count - 1
            If element.All(i).OuterText = sText Then
                element.SetAttribute("SelectedIndex", i.ToString())
                SelectElement(element)
            End If
        Next
    End Sub

    ' 指定された要素にスクロールする (AutoScrollToElement が有効な場合のみ)
    Public Sub ScrollToElement(ByRef element As HtmlElement)
        If Not AutoScrollToElement Then Return
        Dim script As String = $"document.getElementById('{element.Id}').scrollIntoView();"
        Document.InvokeScript("execScript", New Object() {script, "JavaScript"})
    End Sub
#End Region

#Region "その他"
    ' 指定された開始文字と終了文字でテキストを抽出
    Public Function Extract(ByVal sText As String, ByVal sStart As String, ByVal sEnd As String) As List(Of String)
        Dim lstResult As New List(Of String)
        Dim r As New System.Text.RegularExpressions.Regex(sStart & "(.*?)" & sEnd, System.Text.RegularExpressions.RegexOptions.IgnoreCase)
        Dim mc As System.Text.RegularExpressions.MatchCollection = r.Matches(sText)
        For Each m As System.Text.RegularExpressions.Match In mc
            lstResult.Add(m.Groups(1).Value)
        Next
        Return lstResult
    End Function

    ' 指定された開始文字と終了文字でテキストをカット
    Function Cut(ByRef sText As String, ByVal sStart As String, ByVal sEnd As String) As String
        Dim sWk As String = sText
        Dim nPos As Integer = 0
        While True
            Dim nPosS As Integer = sWk.IndexOf(sStart, nPos)
            If nPosS < 0 Then Return sWk
            Dim nPosE As Integer = sWk.IndexOf(sEnd, nPosS + sStart.Length)
            If nPosE < 0 Then Return sWk
            sWk = sWk.Substring(0, nPosS) + sWk.Substring(nPosE + 1)
            nPos = nPosS + 1
        End While
        Return sWk
    End Function
#End Region

End Class
