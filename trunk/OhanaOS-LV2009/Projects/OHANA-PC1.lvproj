<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="9008000">
	<Property Name="varPersistentID:{43049163-27D1-4D33-BAEC-1029ED8E246B}" Type="Ref">/My Computer/FringeScanner.lvlib/FrameRate</Property>
	<Property Name="varPersistentID:{98BE5073-E5BB-426C-B455-DD2FF5F99928}" Type="Ref">/My Computer/FringeScanner.lvlib/FramePerFringe</Property>
	<Property Name="varPersistentID:{FBB4F9C2-2DF8-4AF3-8FF8-4E63E3C66AA4}" Type="Ref">/My Computer/FringeScanner.lvlib/ScanOpd</Property>
	<Property Name="varPersistentID:{FCF2BC96-52FE-4FDD-BACB-73750BAA0273}" Type="Ref">/My Computer/CentralCarriage.lvlib/PhysicalPosition</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="CentralCarriage.lvlib" Type="Library" URL="../../Instruments/CentralCarriage/CentralCarriage.lvlib"/>
		<Item Name="FringeScanner.lvlib" Type="Library" URL="../../Instruments/FringeScanner/FringeScanner.lvlib"/>
		<Item Name="Server.vi" Type="VI" URL="../../Server/Server.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="user.lib" Type="Folder">
				<Item Name="Close Generic Object Refnum__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Close Generic Object Refnum__ogtk.vi"/>
				<Item Name="Close Generic Object Refnum (Array)__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Close Generic Object Refnum (Array)__ogtk.vi"/>
				<Item Name="Close Generic Object Refnum (Scalar)__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Close Generic Object Refnum (Scalar)__ogtk.vi"/>
				<Item Name="Close Generic Object Refnum (Scalar VI)__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Close Generic Object Refnum (Scalar VI)__ogtk.vi"/>
				<Item Name="Close Generic Object Refnum (Array VI)__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Close Generic Object Refnum (Array VI)__ogtk.vi"/>
				<Item Name="Read Key (Variant)__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/variantconfig/variantconfig.llb/Read Key (Variant)__ogtk.vi"/>
				<Item Name="Get TDEnum from Data__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get TDEnum from Data__ogtk.vi"/>
				<Item Name="Type Descriptor Enumeration__ogtk.ctl" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Type Descriptor Enumeration__ogtk.ctl"/>
				<Item Name="Get Header from TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Header from TD__ogtk.vi"/>
				<Item Name="Type Descriptor__ogtk.ctl" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Type Descriptor__ogtk.ctl"/>
				<Item Name="Type Descriptor Header__ogtk.ctl" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Type Descriptor Header__ogtk.ctl"/>
				<Item Name="Get Data Name__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Data Name__ogtk.vi"/>
				<Item Name="Get Data Name from TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Data Name from TD__ogtk.vi"/>
				<Item Name="Get PString__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get PString__ogtk.vi"/>
				<Item Name="Get Last PString__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Last PString__ogtk.vi"/>
				<Item Name="Build Error Cluster__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/error/error.llb/Build Error Cluster__ogtk.vi"/>
				<Item Name="Encode Section and Key Names__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/variantconfig/variantconfig.llb/Encode Section and Key Names__ogtk.vi"/>
				<Item Name="Set Enum String Value__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Set Enum String Value__ogtk.vi"/>
				<Item Name="Variant to Header Info__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Variant to Header Info__ogtk.vi"/>
				<Item Name="Get Strings from Enum__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Strings from Enum__ogtk.vi"/>
				<Item Name="Get Strings from Enum TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Strings from Enum TD__ogtk.vi"/>
				<Item Name="Strip Units__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Strip Units__ogtk.vi"/>
				<Item Name="Get Array Element TDEnum__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Array Element TDEnum__ogtk.vi"/>
				<Item Name="Array Size(s)__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Array Size(s)__ogtk.vi"/>
				<Item Name="Reshape Array to 1D VArray__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Reshape Array to 1D VArray__ogtk.vi"/>
				<Item Name="Set Data Name__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Set Data Name__ogtk.vi"/>
				<Item Name="Reshape 1D Array__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Reshape 1D Array__ogtk.vi"/>
				<Item Name="Get Array Element TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Array Element TD__ogtk.vi"/>
				<Item Name="Get Element TD from Array TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Element TD from Array TD__ogtk.vi"/>
				<Item Name="Array of VData to VArray__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Array of VData to VArray__ogtk.vi"/>
				<Item Name="Get Default Data from TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Default Data from TD__ogtk.vi"/>
				<Item Name="Array of VData to VCluster__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Array of VData to VCluster__ogtk.vi"/>
				<Item Name="Split Cluster TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Split Cluster TD__ogtk.vi"/>
				<Item Name="Cluster to Array of VData__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Cluster to Array of VData__ogtk.vi"/>
				<Item Name="Parse String with TDs__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Parse String with TDs__ogtk.vi"/>
				<Item Name="Fit VI window to Content__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Fit VI window to Content__ogtk.vi"/>
				<Item Name="Current VIs Parents Ref__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Current VIs Parents Ref__ogtk.vi"/>
				<Item Name="Get All Control Values {Variant}__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Get All Control Values {Variant}__ogtk.vi"/>
				<Item Name="Set Control Value {Variant}__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/appcontrol/appcontrol.llb/Set Control Value {Variant}__ogtk.vi"/>
			</Item>
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Merge Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Merge Errors.vi"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
			</Item>
			<Item Name="PathConfigurations.vi" Type="VI" URL="../../Instruments/Files/PathConfigurations.vi"/>
			<Item Name="ServerRunProcess.vi" Type="VI" URL="../../Server/Ressources/ServerRunProcess.vi"/>
			<Item Name="ProcessState-WaitOnRunning.vi" Type="VI" URL="../../Instruments/Process/ProcessState-WaitOnRunning.vi"/>
			<Item Name="ProcessState.ctl" Type="VI" URL="../../Instruments/Process/ProcessState.ctl"/>
			<Item Name="ServerConfigureProcess.vi" Type="VI" URL="../../Server/Ressources/ServerConfigureProcess.vi"/>
			<Item Name="ServerCreateProcess.vi" Type="VI" URL="../../Server/Ressources/ServerCreateProcess.vi"/>
			<Item Name="PathInstruments.vi" Type="VI" URL="../../Instruments/Files/PathInstruments.vi"/>
			<Item Name="ProcessState-WaitOnStoppped.vi" Type="VI" URL="../../Instruments/Process/ProcessState-WaitOnStoppped.vi"/>
			<Item Name="ProcessControl-Stop.vi" Type="VI" URL="../../Instruments/Process/ProcessControl-Stop.vi"/>
			<Item Name="ProcessControl.ctl" Type="VI" URL="../../Instruments/Process/ProcessControl.ctl"/>
			<Item Name="NicmosStart.vi" Type="VI" URL="../../Instruments/Nicmos/Clients/NicmosStart.vi"/>
			<Item Name="NICMOS.COMMAND.ctl" Type="VI" URL="../../Instruments/Nicmos/Controls/NICMOS.COMMAND.ctl"/>
			<Item Name="NICMOS.COMMANDBASIC.ctl" Type="VI" URL="../../Instruments/Nicmos/Controls/NICMOS.COMMANDBASIC.ctl"/>
			<Item Name="NICMOS.READOUT.ctl" Type="VI" URL="../../Instruments/Nicmos/Controls/NICMOS.READOUT.ctl"/>
			<Item Name="NICMOS.FILTERCOMMAND.ctl" Type="VI" URL="../../Instruments/Nicmos/Controls/NICMOS.FILTERCOMMAND.ctl"/>
			<Item Name="NICMOS.FILTER.ctl" Type="VI" URL="../../Instruments/Nicmos/Controls/NICMOS.FILTER.ctl"/>
			<Item Name="NicmosStop.vi" Type="VI" URL="../../Instruments/Nicmos/Clients/NicmosStop.vi"/>
			<Item Name="NICMOS.STATE.ctl" Type="VI" URL="../../Instruments/Nicmos/Controls/NICMOS.STATE.ctl"/>
			<Item Name="NicmosSetReadout.vi" Type="VI" URL="../../Instruments/Nicmos/Clients/NicmosSetReadout.vi"/>
			<Item Name="Occurence-Wait.vi" Type="VI" URL="../../Instruments/Process/Occurence-Wait.vi"/>
			<Item Name="ComputePiezoParameters.vi" Type="VI" URL="../../Instruments/FringeScanner/ComputePiezoParameters.vi"/>
			<Item Name="PIEZO.WAVE.ctl" Type="VI" URL="../../Instruments/Piezo/Controls/PIEZO.WAVE.ctl"/>
			<Item Name="PiezoStart.vi" Type="VI" URL="../../Instruments/Piezo/Clients/PiezoStart.vi"/>
			<Item Name="PIEZO.STATE.ctl" Type="VI" URL="../../Instruments/Piezo/Controls/PIEZO.STATE.ctl"/>
			<Item Name="PIEZO.COMMAND.ctl" Type="VI" URL="../../Instruments/Piezo/Controls/PIEZO.COMMAND.ctl"/>
			<Item Name="PIEZO.COMMANDBASIC.ctl" Type="VI" URL="../../Instruments/Piezo/Controls/PIEZO.COMMANDBASIC.ctl"/>
			<Item Name="PiezoStop.vi" Type="VI" URL="../../Instruments/Piezo/Clients/PiezoStop.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
