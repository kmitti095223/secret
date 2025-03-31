<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class MainForm
	Inherits System.Windows.Forms.Form

	'フォームがコンポーネントの一覧をクリーンアップするために dispose をオーバーライドします。
	<System.Diagnostics.DebuggerNonUserCode()> _
	Protected Overrides Sub Dispose(ByVal disposing As Boolean)
		Try
			If disposing AndAlso components IsNot Nothing Then
				components.Dispose()
			End If
		Finally
			MyBase.Dispose(disposing)
		End Try
	End Sub

	'Windows フォーム デザイナーで必要です。
	Private components As System.ComponentModel.IContainer

	'メモ: 以下のプロシージャは Windows フォーム デザイナーで必要です。
	'Windows フォーム デザイナーを使用して変更できます。  
	'コード エディターを使って変更しないでください。
	<System.Diagnostics.DebuggerStepThrough()> _
	Private Sub InitializeComponent()
		Me.SplitContainer1 = New System.Windows.Forms.SplitContainer()
		Me.SplitContainer2 = New System.Windows.Forms.SplitContainer()
		Me.m_PicL = New MergeImage.PictureBoxEx()
		Me.m_PicR = New MergeImage.PictureBoxEx()
		Me.m_PicM = New MergeImage.PictureBoxEx()
		Me.Button1 = New System.Windows.Forms.Button()
		CType(Me.SplitContainer1, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.SplitContainer1.Panel1.SuspendLayout()
		Me.SplitContainer1.Panel2.SuspendLayout()
		Me.SplitContainer1.SuspendLayout()
		CType(Me.SplitContainer2, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.SplitContainer2.Panel1.SuspendLayout()
		Me.SplitContainer2.Panel2.SuspendLayout()
		Me.SplitContainer2.SuspendLayout()
		CType(Me.m_PicL, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.m_PicR, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.m_PicM, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.SuspendLayout()
		'
		'SplitContainer1
		'
		Me.SplitContainer1.Dock = System.Windows.Forms.DockStyle.Fill
		Me.SplitContainer1.Location = New System.Drawing.Point(0, 0)
		Me.SplitContainer1.Name = "SplitContainer1"
		Me.SplitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal
		'
		'SplitContainer1.Panel1
		'
		Me.SplitContainer1.Panel1.Controls.Add(Me.SplitContainer2)
		'
		'SplitContainer1.Panel2
		'
		Me.SplitContainer1.Panel2.Controls.Add(Me.m_PicM)
		Me.SplitContainer1.Size = New System.Drawing.Size(1022, 632)
		Me.SplitContainer1.SplitterDistance = 373
		Me.SplitContainer1.TabIndex = 0
		'
		'SplitContainer2
		'
		Me.SplitContainer2.Dock = System.Windows.Forms.DockStyle.Fill
		Me.SplitContainer2.Location = New System.Drawing.Point(0, 0)
		Me.SplitContainer2.Name = "SplitContainer2"
		'
		'SplitContainer2.Panel1
		'
		Me.SplitContainer2.Panel1.Controls.Add(Me.m_PicL)
		'
		'SplitContainer2.Panel2
		'
		Me.SplitContainer2.Panel2.Controls.Add(Me.m_PicR)
		Me.SplitContainer2.Size = New System.Drawing.Size(1022, 373)
		Me.SplitContainer2.SplitterDistance = 540
		Me.SplitContainer2.TabIndex = 0
		'
		'm_PicL
		'
		Me.m_PicL.AllowDrop = True
		Me.m_PicL.Dock = System.Windows.Forms.DockStyle.Fill
		Me.m_PicL.Location = New System.Drawing.Point(0, 0)
		Me.m_PicL.Name = "m_PicL"
		Me.m_PicL.Size = New System.Drawing.Size(540, 373)
		Me.m_PicL.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
		Me.m_PicL.TabIndex = 0
		Me.m_PicL.TabStop = False
		'
		'm_PicR
		'
		Me.m_PicR.AllowDrop = True
		Me.m_PicR.Dock = System.Windows.Forms.DockStyle.Fill
		Me.m_PicR.Location = New System.Drawing.Point(0, 0)
		Me.m_PicR.Name = "m_PicR"
		Me.m_PicR.Size = New System.Drawing.Size(478, 373)
		Me.m_PicR.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
		Me.m_PicR.TabIndex = 1
		Me.m_PicR.TabStop = False
		'
		'm_PicM
		'
		Me.m_PicM.AllowDrop = True
		Me.m_PicM.Dock = System.Windows.Forms.DockStyle.Fill
		Me.m_PicM.Location = New System.Drawing.Point(0, 0)
		Me.m_PicM.Name = "m_PicM"
		Me.m_PicM.Size = New System.Drawing.Size(1022, 255)
		Me.m_PicM.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
		Me.m_PicM.TabIndex = 1
		Me.m_PicM.TabStop = False
		'
		'Button1
		'
		Me.Button1.Location = New System.Drawing.Point(0, 0)
		Me.Button1.Name = "Button1"
		Me.Button1.Size = New System.Drawing.Size(171, 82)
		Me.Button1.TabIndex = 1
		Me.Button1.Text = "Button1"
		Me.Button1.UseVisualStyleBackColor = True
		'
		'MainForm
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(1022, 632)
		Me.Controls.Add(Me.Button1)
		Me.Controls.Add(Me.SplitContainer1)
		Me.Name = "MainForm"
		Me.Text = "Form1"
		Me.SplitContainer1.Panel1.ResumeLayout(False)
		Me.SplitContainer1.Panel2.ResumeLayout(False)
		CType(Me.SplitContainer1, System.ComponentModel.ISupportInitialize).EndInit()
		Me.SplitContainer1.ResumeLayout(False)
		Me.SplitContainer2.Panel1.ResumeLayout(False)
		Me.SplitContainer2.Panel2.ResumeLayout(False)
		CType(Me.SplitContainer2, System.ComponentModel.ISupportInitialize).EndInit()
		Me.SplitContainer2.ResumeLayout(False)
		CType(Me.m_PicL, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.m_PicR, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.m_PicM, System.ComponentModel.ISupportInitialize).EndInit()
		Me.ResumeLayout(False)

	End Sub

	Friend WithEvents SplitContainer1 As SplitContainer
	Friend WithEvents SplitContainer2 As SplitContainer
	Friend WithEvents m_PicL As PictureBoxEx
	Friend WithEvents m_PicR As PictureBoxEx
	Friend WithEvents m_PicM As PictureBoxEx
	Friend WithEvents Button1 As Button
End Class
