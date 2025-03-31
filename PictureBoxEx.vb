Imports System.Windows.Forms
Imports System.Drawing
Imports System.IO

Public Class PictureBoxEx
    Inherits PictureBox

    Private originalImage As Image
    Private isOriginalSize As Boolean = False
    Private scrollParent As Panel
    Private clickPosition As Point? = Nothing
    Private imageFilePath As String

    Public Sub New()
        Me.SizeMode = PictureBoxSizeMode.Zoom
        Me.AllowDrop = True
    End Sub

    Public Sub LoadImage(filePath As String)
        If File.Exists(filePath) AndAlso Path.GetExtension(filePath).ToLower() = ".png" Then
            originalImage = Image.FromFile(filePath)
            Me.Image = originalImage
            imageFilePath = filePath
            FitToControl()
        End If
    End Sub

    Public Function GetFileName() As String
        If String.IsNullOrEmpty(imageFilePath) Then
            Return String.Empty
        End If
        Return imageFilePath
    End Function

    Public Sub SetClickPosition(x As Integer, y As Integer)
        clickPosition = New Point(x, y)
        Me.Invalidate() ' 再描画を要求
    End Sub
    Public Function GetClickPosition() As Point
        If clickPosition.HasValue AndAlso Me.Image IsNot Nothing Then
            Dim img As Image = Me.Image
            Dim pbWidth As Integer = Me.ClientSize.Width
            Dim pbHeight As Integer = Me.ClientSize.Height
            Dim imgWidth As Integer = img.Width
            Dim imgHeight As Integer = img.Height

            Dim scaleX As Double = imgWidth / pbWidth
            Dim scaleY As Double = imgHeight / pbHeight

            Dim imgX As Integer = CInt(clickPosition.Value.X * scaleX)
            Dim imgY As Integer = CInt(clickPosition.Value.Y * scaleY)

            Return New Point(imgX, imgY)
        End If
        Return Point.Empty
    End Function

    Private Sub FitToControl()
        Me.SizeMode = PictureBoxSizeMode.Zoom
        Me.Dock = DockStyle.Fill
        isOriginalSize = False
    End Sub

    Private Sub ShowOriginalSize(clickPoint As Point)
        Me.SizeMode = PictureBoxSizeMode.AutoSize
        Me.Dock = DockStyle.None
        isOriginalSize = True

        If Me.Parent IsNot Nothing AndAlso TypeOf Me.Parent Is Panel Then
            scrollParent = CType(Me.Parent, Panel)
            scrollParent.AutoScroll = True

            Dim imgWidth As Integer = originalImage.Width
            Dim imgHeight As Integer = originalImage.Height
            Dim panelWidth As Integer = scrollParent.ClientSize.Width
            Dim panelHeight As Integer = scrollParent.ClientSize.Height

            Dim offsetX As Integer = Math.Max(0, clickPoint.X - panelWidth \ 2)
            Dim offsetY As Integer = Math.Max(0, clickPoint.Y - panelHeight \ 2)

            scrollParent.AutoScrollPosition = New Point(offsetX, offsetY)
        End If
    End Sub


    Protected Overrides Sub OnPaint(e As PaintEventArgs)
        MyBase.OnPaint(e)
        If clickPosition.HasValue Then
            Using pen As New Pen(Color.Red, 2)
                Dim size As Integer = 20
                Dim halfSize As Integer = size \ 2
                Dim center As Point = clickPosition.Value

                e.Graphics.DrawLine(pen, center.X - halfSize, center.Y - halfSize, center.X + halfSize, center.Y + halfSize)
                e.Graphics.DrawLine(pen, center.X - halfSize, center.Y + halfSize, center.X + halfSize, center.Y - halfSize)
            End Using
        End If
    End Sub

    Private Sub PictureBoxEx_MouseClick(sender As Object, e As MouseEventArgs) Handles Me.MouseClick

        If e.Button = MouseButtons.Left Then
            SetClickPosition(e.X, e.Y)
        End If
    End Sub

    Private Sub PictureBoxEx_DragEnter(sender As Object, e As DragEventArgs) Handles Me.DragEnter
        If e.Data.GetDataPresent(DataFormats.FileDrop) Then
            Dim files As String() = CType(e.Data.GetData(DataFormats.FileDrop), String())
            If files.Length > 0 AndAlso Path.GetExtension(files(0)).ToLower() = ".png" Then
                e.Effect = DragDropEffects.Copy
            End If
        End If
    End Sub

    Private Sub PictureBoxEx_DragDrop(sender As Object, e As DragEventArgs) Handles Me.DragDrop
        Dim files As String() = CType(e.Data.GetData(DataFormats.FileDrop), String())
        If files.Length > 0 Then
            LoadImage(files(0))
        End If
    End Sub

    Private Sub PictureBoxEx_MouseDoubleClick(sender As Object, e As MouseEventArgs) Handles Me.MouseDoubleClick
        If originalImage Is Nothing Then Exit Sub

        If isOriginalSize Then
            FitToControl()
        Else
            ShowOriginalSize(CType(e, MouseEventArgs).Location)
        End If
    End Sub


End Class
