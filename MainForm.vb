Public Class MainForm
	Private Sub MainForm_Load(sender As Object, e As EventArgs) Handles Me.Load
		m_PicL.LoadImage(Application.StartupPath & "\..\..\Test\Left_01.png")
		m_PicR.LoadImage(Application.StartupPath & "\..\..\Test\Right_01.png")
	End Sub

	Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click

		Merge.Exec(m_PicL.GetFileName, m_PicL.GetClickPosition, m_PicR.GetFileName, m_PicR.GetClickPosition)

	End Sub

End Class
