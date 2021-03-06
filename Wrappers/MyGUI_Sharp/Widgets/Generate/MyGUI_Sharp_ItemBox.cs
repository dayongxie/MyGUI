/*!
	@file
	@author		Generate utility by Albert Semenov
	@date		01/2009
	@module
*/

using System;
using System.Runtime.InteropServices;

namespace MyGUI.Sharp
{

    public  class ItemBox : DDContainer
    {

        #region ItemBox

        protected override string GetWidgetType() { return "ItemBox"; }

        internal static BaseWidget RequestWrapItemBox(BaseWidget _parent, IntPtr _widget)
        {
			ItemBox widget = new ItemBox();
			widget.WrapWidget(_parent, _widget);
            return widget;
        }

        internal static BaseWidget RequestCreateItemBox(BaseWidget _parent, WidgetStyle _style, string _skin, IntCoord _coord, Align _align, string _layer, string _name)
        {
			ItemBox widget = new ItemBox();
			widget.CreateWidgetImpl(_parent, _style, _skin, _coord, _align, _layer, _name);
            return widget;
        }
        
		#endregion
	
		
		//InsertPoint
		#region Event NotifyItem

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBoxEvent_AdviseNotifyItem( IntPtr _native, bool _advise );

		public delegate void HandleNotifyItem(
			 ItemBox _sender ,
			ref IBNotifyItemData _info );
			
		private HandleNotifyItem mEventNotifyItem;
		public event HandleNotifyItem EventNotifyItem
		{
			add
			{
				if (ExportEventNotifyItem.mDelegate == null)
				{
					ExportEventNotifyItem.mDelegate = new ExportEventNotifyItem.ExportHandle( OnExportNotifyItem );
					ExportEventNotifyItem.ExportItemBoxEvent_DelegateNotifyItem( ExportEventNotifyItem.mDelegate );
				}

				if (mEventNotifyItem == null)
					ExportItemBoxEvent_AdviseNotifyItem( mNative, true );
				mEventNotifyItem += value;
			}
			remove
			{
				mEventNotifyItem -= value;
				if (mEventNotifyItem == null)
					ExportItemBoxEvent_AdviseNotifyItem( mNative, false );
			}
		}

		private struct ExportEventNotifyItem
		{
			[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
			public static extern void ExportItemBoxEvent_DelegateNotifyItem( ExportHandle _delegate );
			[UnmanagedFunctionPointer(CallingConvention.StdCall)]
			public delegate void ExportHandle(
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  ItemBox _sender ,
				[In] ref IBNotifyItemData _info );
				
			public static ExportHandle mDelegate;
		}

		private static void OnExportNotifyItem(
			 ItemBox _sender ,
			ref IBNotifyItemData _info )
		{
			if (_sender.mEventNotifyItem != null)
				_sender.mEventNotifyItem(
					 _sender ,
					ref _info );
		}

		#endregion
		#region Event MouseItemActivate

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBoxEvent_AdviseMouseItemActivate( IntPtr _native, bool _advise );

		public delegate void HandleMouseItemActivate(
			 ItemBox _sender ,
			 uint _index );
			
		private HandleMouseItemActivate mEventMouseItemActivate;
		public event HandleMouseItemActivate EventMouseItemActivate
		{
			add
			{
				if (ExportEventMouseItemActivate.mDelegate == null)
				{
					ExportEventMouseItemActivate.mDelegate = new ExportEventMouseItemActivate.ExportHandle( OnExportMouseItemActivate );
					ExportEventMouseItemActivate.ExportItemBoxEvent_DelegateMouseItemActivate( ExportEventMouseItemActivate.mDelegate );
				}

				if (mEventMouseItemActivate == null)
					ExportItemBoxEvent_AdviseMouseItemActivate( mNative, true );
				mEventMouseItemActivate += value;
			}
			remove
			{
				mEventMouseItemActivate -= value;
				if (mEventMouseItemActivate == null)
					ExportItemBoxEvent_AdviseMouseItemActivate( mNative, false );
			}
		}

		private struct ExportEventMouseItemActivate
		{
			[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
			public static extern void ExportItemBoxEvent_DelegateMouseItemActivate( ExportHandle _delegate );
			[UnmanagedFunctionPointer(CallingConvention.StdCall)]
			public delegate void ExportHandle(
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  ItemBox _sender ,
				  uint _index );
				
			public static ExportHandle mDelegate;
		}

		private static void OnExportMouseItemActivate(
			 ItemBox _sender ,
			 uint _index )
		{
			if (_sender.mEventMouseItemActivate != null)
				_sender.mEventMouseItemActivate(
					 _sender ,
					 _index );
		}

		#endregion
		#region Event ChangeItemPosition

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBoxEvent_AdviseChangeItemPosition( IntPtr _native, bool _advise );

		public delegate void HandleChangeItemPosition(
			 ItemBox _sender ,
			 uint _index );
			
		private HandleChangeItemPosition mEventChangeItemPosition;
		public event HandleChangeItemPosition EventChangeItemPosition
		{
			add
			{
				if (ExportEventChangeItemPosition.mDelegate == null)
				{
					ExportEventChangeItemPosition.mDelegate = new ExportEventChangeItemPosition.ExportHandle( OnExportChangeItemPosition );
					ExportEventChangeItemPosition.ExportItemBoxEvent_DelegateChangeItemPosition( ExportEventChangeItemPosition.mDelegate );
				}

				if (mEventChangeItemPosition == null)
					ExportItemBoxEvent_AdviseChangeItemPosition( mNative, true );
				mEventChangeItemPosition += value;
			}
			remove
			{
				mEventChangeItemPosition -= value;
				if (mEventChangeItemPosition == null)
					ExportItemBoxEvent_AdviseChangeItemPosition( mNative, false );
			}
		}

		private struct ExportEventChangeItemPosition
		{
			[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
			public static extern void ExportItemBoxEvent_DelegateChangeItemPosition( ExportHandle _delegate );
			[UnmanagedFunctionPointer(CallingConvention.StdCall)]
			public delegate void ExportHandle(
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  ItemBox _sender ,
				  uint _index );
				
			public static ExportHandle mDelegate;
		}

		private static void OnExportChangeItemPosition(
			 ItemBox _sender ,
			 uint _index )
		{
			if (_sender.mEventChangeItemPosition != null)
				_sender.mEventChangeItemPosition(
					 _sender ,
					 _index );
		}

		#endregion
		#region Event SelectItemAccept

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBoxEvent_AdviseSelectItemAccept( IntPtr _native, bool _advise );

		public delegate void HandleSelectItemAccept(
			 ItemBox _sender ,
			 uint _index );
			
		private HandleSelectItemAccept mEventSelectItemAccept;
		public event HandleSelectItemAccept EventSelectItemAccept
		{
			add
			{
				if (ExportEventSelectItemAccept.mDelegate == null)
				{
					ExportEventSelectItemAccept.mDelegate = new ExportEventSelectItemAccept.ExportHandle( OnExportSelectItemAccept );
					ExportEventSelectItemAccept.ExportItemBoxEvent_DelegateSelectItemAccept( ExportEventSelectItemAccept.mDelegate );
				}

				if (mEventSelectItemAccept == null)
					ExportItemBoxEvent_AdviseSelectItemAccept( mNative, true );
				mEventSelectItemAccept += value;
			}
			remove
			{
				mEventSelectItemAccept -= value;
				if (mEventSelectItemAccept == null)
					ExportItemBoxEvent_AdviseSelectItemAccept( mNative, false );
			}
		}

		private struct ExportEventSelectItemAccept
		{
			[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
			public static extern void ExportItemBoxEvent_DelegateSelectItemAccept( ExportHandle _delegate );
			[UnmanagedFunctionPointer(CallingConvention.StdCall)]
			public delegate void ExportHandle(
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  ItemBox _sender ,
				  uint _index );
				
			public static ExportHandle mDelegate;
		}

		private static void OnExportSelectItemAccept(
			 ItemBox _sender ,
			 uint _index )
		{
			if (_sender.mEventSelectItemAccept != null)
				_sender.mEventSelectItemAccept(
					 _sender ,
					 _index );
		}

		#endregion
		#region Request DrawItem

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBoxEvent_AdviseDrawItem( IntPtr _native, bool _advise );

		public delegate void HandleDrawItem(
			 ItemBox _sender ,
			 Widget _item ,
			ref IBDrawItemInfo _info );
			
		private HandleDrawItem mEventDrawItem;
		public event HandleDrawItem RequestDrawItem
		{
			add
			{
				if (ExportEventDrawItem.mDelegate == null)
				{
					ExportEventDrawItem.mDelegate = new ExportEventDrawItem.ExportHandle( OnExportDrawItem );
					ExportEventDrawItem.ExportItemBoxEvent_DelegateDrawItem( ExportEventDrawItem.mDelegate );
				}

				if (mEventDrawItem == null)
					ExportItemBoxEvent_AdviseDrawItem( mNative, true );
				mEventDrawItem += value;
			}
			remove
			{
				mEventDrawItem -= value;
				if (mEventDrawItem == null)
					ExportItemBoxEvent_AdviseDrawItem( mNative, false );
			}
		}

		private struct ExportEventDrawItem
		{
			[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
			public static extern void ExportItemBoxEvent_DelegateDrawItem( ExportHandle _delegate );
			[UnmanagedFunctionPointer(CallingConvention.StdCall)]
			public delegate void ExportHandle(
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  ItemBox _sender ,
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  Widget _item ,
				[In] ref IBDrawItemInfo _info );
				
			public static ExportHandle mDelegate;
		}

		private static void OnExportDrawItem(
			 ItemBox _sender ,
			 Widget _item ,
			ref IBDrawItemInfo _info )
		{
			if (_sender.mEventDrawItem != null)
				_sender.mEventDrawItem(
					 _sender ,
					 _item ,
					ref _info );
		}

		#endregion
		#region Request CoordItem

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBoxEvent_AdviseCoordItem( IntPtr _native, bool _advise );

		public delegate void HandleCoordItem(
			 ItemBox _sender ,
			ref IntCoord _coord ,
			 bool _drag );
			
		private HandleCoordItem mEventCoordItem;
		public event HandleCoordItem RequestCoordItem
		{
			add
			{
				if (ExportEventCoordItem.mDelegate == null)
				{
					ExportEventCoordItem.mDelegate = new ExportEventCoordItem.ExportHandle( OnExportCoordItem );
					ExportEventCoordItem.ExportItemBoxEvent_DelegateCoordItem( ExportEventCoordItem.mDelegate );
				}

				if (mEventCoordItem == null)
					ExportItemBoxEvent_AdviseCoordItem( mNative, true );
				mEventCoordItem += value;
			}
			remove
			{
				mEventCoordItem -= value;
				if (mEventCoordItem == null)
					ExportItemBoxEvent_AdviseCoordItem( mNative, false );
			}
		}

		private struct ExportEventCoordItem
		{
			[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
			public static extern void ExportItemBoxEvent_DelegateCoordItem( ExportHandle _delegate );
			[UnmanagedFunctionPointer(CallingConvention.StdCall)]
			public delegate void ExportHandle(
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  ItemBox _sender ,
				[In, Out] ref IntCoord _coord ,
				[MarshalAs(UnmanagedType.U1)]  bool _drag );
				
			public static ExportHandle mDelegate;
		}

		private static void OnExportCoordItem(
			 ItemBox _sender ,
			ref IntCoord _coord ,
			 bool _drag )
		{
			if (_sender.mEventCoordItem != null)
				_sender.mEventCoordItem(
					 _sender ,
					ref _coord ,
					 _drag );
		}

		#endregion
		#region Request CreateWidgetItem

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBoxEvent_AdviseCreateWidgetItem( IntPtr _native, bool _advise );

		public delegate void HandleCreateWidgetItem(
			 ItemBox _sender ,
			 Widget _item );
			
		private HandleCreateWidgetItem mEventCreateWidgetItem;
		public event HandleCreateWidgetItem RequestCreateWidgetItem
		{
			add
			{
				if (ExportEventCreateWidgetItem.mDelegate == null)
				{
					ExportEventCreateWidgetItem.mDelegate = new ExportEventCreateWidgetItem.ExportHandle( OnExportCreateWidgetItem );
					ExportEventCreateWidgetItem.ExportItemBoxEvent_DelegateCreateWidgetItem( ExportEventCreateWidgetItem.mDelegate );
				}

				if (mEventCreateWidgetItem == null)
					ExportItemBoxEvent_AdviseCreateWidgetItem( mNative, true );
				mEventCreateWidgetItem += value;
			}
			remove
			{
				mEventCreateWidgetItem -= value;
				if (mEventCreateWidgetItem == null)
					ExportItemBoxEvent_AdviseCreateWidgetItem( mNative, false );
			}
		}

		private struct ExportEventCreateWidgetItem
		{
			[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
			public static extern void ExportItemBoxEvent_DelegateCreateWidgetItem( ExportHandle _delegate );
			[UnmanagedFunctionPointer(CallingConvention.StdCall)]
			public delegate void ExportHandle(
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  ItemBox _sender ,
				[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  Widget _item );
				
			public static ExportHandle mDelegate;
		}

		private static void OnExportCreateWidgetItem(
			 ItemBox _sender ,
			 Widget _item )
		{
			if (_sender.mEventCreateWidgetItem != null)
				_sender.mEventCreateWidgetItem(
					 _sender ,
					 _item );
		}

		#endregion
		#region Method SetCoord

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_SetCoord_left_top_width_height( IntPtr _native ,
			  int _left ,
			  int _top ,
			  int _width ,
			  int _height );

		public void SetCoord(
			int _left ,
			int _top ,
			int _width ,
			int _height )
		{
			ExportItemBox_SetCoord_left_top_width_height( mNative , 
				 _left ,
				 _top ,
				 _width ,
				 _height );
		}

		#endregion
		#region Method SetSize

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_SetSize_width_height( IntPtr _native ,
			  int _width ,
			  int _height );

		public void SetSize(
			int _width ,
			int _height )
		{
			ExportItemBox_SetSize_width_height( mNative , 
				 _width ,
				 _height );
		}

		#endregion
		#region Method SetPosition

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_SetPosition_left_top( IntPtr _native ,
			  int _left ,
			  int _top );

		public void SetPosition(
			int _left ,
			int _top )
		{
			ExportItemBox_SetPosition_left_top( mNative , 
				 _left ,
				 _top );
		}

		#endregion
		#region Method ResetDrag

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_ResetDrag( IntPtr _native );

		public void ResetDrag( )
		{
			ExportItemBox_ResetDrag(  mNative );
		}

		#endregion
		#region Method GetWidgetByIndex

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]
		private static extern Widget ExportItemBox_GetWidgetByIndex_index( IntPtr _native ,
			  uint _index );

		public Widget GetWidgetByIndex(
			uint _index )
		{
			return  ExportItemBox_GetWidgetByIndex_index( mNative , 
				 _index )  ;
		}

		#endregion
		#region Method GetIndexByWidget

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
        
		private static extern uint ExportItemBox_GetIndexByWidget_widget( IntPtr _native ,
			[MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]  BaseWidget _widget );

		public uint GetIndexByWidget(
			Widget _widget )
		{
			return  ExportItemBox_GetIndexByWidget_widget( mNative , 
				 _widget )  ;
		}

		#endregion
		#region Method GetItemDataAt

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.IUnknown)]
		private static extern object ExportItemBox_GetItemDataAt_index( IntPtr _native ,
			  uint _index );

		public object GetItemDataAt(
			uint _index )
		{
			return ExportItemBox_GetItemDataAt_index( mNative , 
				 _index );
		}

		#endregion
		#region Method ClearItemDataAt

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_ClearItemDataAt_index( IntPtr _native ,
			  uint _index );

		public void ClearItemDataAt(
			uint _index )
		{
			ExportItemBox_ClearItemDataAt_index( mNative , 
				 _index );
		}

		#endregion
		#region Method SetItemDataAt

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_SetItemDataAt_index_data( IntPtr _native ,
			  uint _index ,
			[MarshalAs(UnmanagedType.IUnknown)]  object _data );

		public void SetItemDataAt(
			uint _index ,
			object _data )
		{
			ExportItemBox_SetItemDataAt_index_data( mNative , 
				 _index ,
				 _data );
		}

		#endregion
		#region Method ClearIndexSelected

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_ClearIndexSelected( IntPtr _native );

		public void ClearIndexSelected( )
		{
			ExportItemBox_ClearIndexSelected(  mNative );
		}

		#endregion
		#region Method RedrawAllItems

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_RedrawAllItems( IntPtr _native );

		public void RedrawAllItems( )
		{
			ExportItemBox_RedrawAllItems(  mNative );
		}

		#endregion
		#region Method RedrawItemAt

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_RedrawItemAt_index( IntPtr _native ,
			  uint _index );

		public void RedrawItemAt(
			uint _index )
		{
			ExportItemBox_RedrawItemAt_index( mNative , 
				 _index );
		}

		#endregion
		#region Method RemoveAllItems

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_RemoveAllItems( IntPtr _native );

		public void RemoveAllItems( )
		{
			ExportItemBox_RemoveAllItems(  mNative );
		}

		#endregion
		#region Method RemoveItemAt

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_RemoveItemAt_index( IntPtr _native ,
			  uint _index );

		public void RemoveItemAt(
			uint _index )
		{
			ExportItemBox_RemoveItemAt_index( mNative , 
				 _index );
		}

		#endregion
		#region Method AddItem

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_AddItem_data( IntPtr _native ,
			[MarshalAs(UnmanagedType.IUnknown)]  object _data );

		public void AddItem(
			object _data )
		{
			ExportItemBox_AddItem_data( mNative , 
				 _data );
		}

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_AddItem( IntPtr _native );

		public void AddItem( )
		{
			ExportItemBox_AddItem( mNative );
		}

		#endregion
		#region Method InsertItemAt

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_InsertItemAt_index_data( IntPtr _native ,
			  uint _index ,
			[MarshalAs(UnmanagedType.IUnknown)]  object _data );

		public void InsertItemAt(
			uint _index ,
			object _data )
		{
			ExportItemBox_InsertItemAt_index_data( mNative , 
				 _index ,
				 _data );
		}

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_InsertItemAt_index( IntPtr _native ,
			  uint _index );

		public void InsertItemAt(
			uint _index )
		{
			ExportItemBox_InsertItemAt_index( mNative , 
				 _index );
		}

		#endregion
		#region Property WidgetDrag

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(InterfaceMarshaler))]
		private static extern Widget ExportItemBox_GetWidgetDrag( IntPtr _native );

		public Widget WidgetDrag
		{
			get { return  ExportItemBox_GetWidgetDrag( mNative )  ; }
		}

		#endregion
		#region Property VerticalAlignment

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
		private static extern bool ExportItemBox_GetVerticalAlignment( IntPtr _widget );
		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_SetVerticalAlignment( IntPtr _widget, [MarshalAs(UnmanagedType.U1)]  bool _value );

		public bool VerticalAlignment
		{
			get { return  ExportItemBox_GetVerticalAlignment( mNative )  ; }
			set { ExportItemBox_SetVerticalAlignment( mNative,  value ); }
		}

		#endregion
		#region Property IndexSelected

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
        
		private static extern uint ExportItemBox_GetIndexSelected( IntPtr _widget );
		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
		private static extern void ExportItemBox_SetIndexSelected( IntPtr _widget,   uint _value );

		public uint IndexSelected
		{
			get { return  ExportItemBox_GetIndexSelected( mNative )  ; }
			set { ExportItemBox_SetIndexSelected( mNative,  value ); }
		}

		#endregion
		#region Property ItemCount

		[DllImport("MyGUI_Export", CallingConvention = CallingConvention.Cdecl)]
        
		private static extern uint ExportItemBox_GetItemCount( IntPtr _native );

		public uint ItemCount
		{
			get { return  ExportItemBox_GetItemCount( mNative )  ; }
		}

		#endregion
		
    }

}
