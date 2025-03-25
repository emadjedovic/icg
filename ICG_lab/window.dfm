object ICG_app: TICG_app
  Left = 0
  Top = 0
  Caption = 'ICG_app'
  ClientHeight = 478
  ClientWidth = 604
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Image: TImage
    Left = 8
    Top = 48
    Width = 588
    Height = 321
    OnMouseDown = ImageMouseDown
  end
  object ButtonSimplePolygon: TButton
    Left = 208
    Top = 384
    Width = 201
    Height = 65
    Caption = 'Simple Polygon'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'JetBrains Mono'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = ButtonSimplePolygonClick
  end
end
