<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="9008000">
	<Property Name="varPersistentID:{2E37B4F2-DAFE-4F72-9624-A3A112241522}" Type="Ref">/My Computer/DelayGenerator.lvlib/Target</Property>
	<Property Name="varPersistentID:{57855705-2175-4760-B2D4-40E3CDED5918}" Type="Ref">/My Computer/DelayGenerator.lvlib/Baseline</Property>
	<Property Name="varPersistentID:{AEADB6C8-F43A-423F-850C-ADD28707FA68}" Type="Ref">/My Computer/DelayGenerator.lvlib/SiteInformation</Property>
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
		<Item Name="FringeTracker.lvlib" Type="Library" URL="../../Instruments/FringeTracker/FringeTracker.lvlib"/>
		<Item Name="Aerotech.lvlib" Type="Library" URL="../../Instruments/Aerotech/Aerotech.lvlib"/>
		<Item Name="CentralCarriage.lvlib" Type="Library" URL="../../Instruments/CentralCarriage/CentralCarriage.lvlib"/>
		<Item Name="DelayGenerator.lvlib" Type="Library" URL="../../Instruments/DelayGenerator/DelayGenerator.lvlib"/>
		<Item Name="Server.vi" Type="VI" URL="../../Server/Server.vi"/>
		<Item Name="ServerGUI.vi" Type="VI" URL="../../Server/ServerGUI.vi"/>
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
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
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
			<Item Name="NICMOS.READOUT.ctl" Type="VI" URL="../../Instruments/Nicmos/Controls/NICMOS.READOUT.ctl"/>
			<Item Name="StarAstrometricEntry.ctl" Type="VI" URL="../../Instruments/DelayGenerator/Controls/StarAstrometricEntry.ctl"/>
			<Item Name="SiteInformation.ctl" Type="VI" URL="../../Instruments/DelayGenerator/Controls/SiteInformation.ctl"/>
			<Item Name="Baseline.ctl" Type="VI" URL="../../Instruments/DelayGenerator/Controls/Baseline.ctl"/>
			<Item Name="DelayTarget.ctl" Type="VI" URL="../../Instruments/DelayGenerator/Controls/DelayTarget.ctl"/>
			<Item Name="lvanlys.dll" Type="Document" URL="../../../Program Files/National Instruments/LabVIEW 2009/resource/lvanlys.dll"/>
			<Item Name="CrossProduct.vi" Type="VI" URL="../../Instruments/DelayGenerator/Math/CrossProduct.vi"/>
			<Item Name="equ2hor.vi" Type="VI" URL="../../Instruments/DelayGenerator/Novas-C/equ2hor.vi"/>
			<Item Name="novas-dll.dll" Type="Document" URL="../../Instruments/DelayGenerator/Novas-C/novas-dll.dll"/>
			<Item Name="TimeStampToJulianDate.vi" Type="VI" URL="../../Instruments/DelayGenerator/Novas-C/TimeStampToJulianDate.vi"/>
			<Item Name="topo_star.vi" Type="VI" URL="../../Instruments/DelayGenerator/Novas-C/topo_star.vi"/>
			<Item Name="ProcessState-Starting.vi" Type="VI" URL="../../Instruments/Process/ProcessState-Starting.vi"/>
			<Item Name="ProcessControl-WaitOnStop.vi" Type="VI" URL="../../Instruments/Process/ProcessControl-WaitOnStop.vi"/>
			<Item Name="DelayGeneratorOpenSynchronization.vi" Type="VI" URL="../../Instruments/DelayGenerator/Controller/DelayGeneratorOpenSynchronization.vi"/>
			<Item Name="DelayGeneratorSynchro.ctl" Type="VI" URL="../../Instruments/DelayGenerator/Controls/DelayGeneratorSynchro.ctl"/>
			<Item Name="DelayGeneratorCommand.ctl" Type="VI" URL="../../Instruments/DelayGenerator/Controls/DelayGeneratorCommand.ctl"/>
			<Item Name="DelayGeneratorState.ctl" Type="VI" URL="../../Instruments/DelayGenerator/Controls/DelayGeneratorState.ctl"/>
			<Item Name="AerotechTarget.ctl" Type="VI" URL="../../Instruments/Aerotech/Controls/AerotechTarget.ctl"/>
			<Item Name="ProcessState-Stopped.vi" Type="VI" URL="../../Instruments/Process/ProcessState-Stopped.vi"/>
			<Item Name="ProcessState-Stopping.vi" Type="VI" URL="../../Instruments/Process/ProcessState-Stopping.vi"/>
			<Item Name="ProcessState-Running.vi" Type="VI" URL="../../Instruments/Process/ProcessState-Running.vi"/>
			<Item Name="DelayGeneratorCloseSynchronization.vi" Type="VI" URL="../../Instruments/DelayGenerator/Controller/DelayGeneratorCloseSynchronization.vi"/>
			<Item Name="DelayGeneratorIdle.vi" Type="VI" URL="../../Instruments/DelayGenerator/Clients/DelayGeneratorIdle.vi"/>
			<Item Name="DelayGeneratorGetState.vi" Type="VI" URL="../../Instruments/DelayGenerator/Clients/DelayGeneratorGetState.vi"/>
			<Item Name="DelayGeneratorTrack.vi" Type="VI" URL="../../Instruments/DelayGenerator/Clients/DelayGeneratorTrack.vi"/>
			<Item Name="AerotechGetState.vi" Type="VI" URL="../../Instruments/Aerotech/Clients/AerotechGetState.vi"/>
			<Item Name="AerotechState.ctl" Type="VI" URL="../../Instruments/Aerotech/Controls/AerotechState.ctl"/>
			<Item Name="AerotechTrack.vi" Type="VI" URL="../../Instruments/Aerotech/Clients/AerotechTrack.vi"/>
			<Item Name="AerotechCommand.ctl" Type="VI" URL="../../Instruments/Aerotech/Controls/AerotechCommand.ctl"/>
			<Item Name="AerotechStop.vi" Type="VI" URL="../../Instruments/Aerotech/Clients/AerotechStop.vi"/>
			<Item Name="AerotechHome.vi" Type="VI" URL="../../Instruments/Aerotech/Clients/AerotechHome.vi"/>
			<Item Name="AerotechPosition.vi" Type="VI" URL="../../Instruments/Aerotech/Clients/AerotechPosition.vi"/>
			<Item Name="DelayGenerator-StaticBaseline.vi" Type="VI" URL="../../Instruments/DelayGenerator/Controller/DelayGenerator-StaticBaseline.vi"/>
			<Item Name="DelayGenerator-CentralCarriage.vi" Type="VI" URL="../../Instruments/DelayGenerator/Controller/DelayGenerator-CentralCarriage.vi"/>
			<Item Name="DelayGenerator-FringeScannerOffset.vi" Type="VI" URL="../../Instruments/DelayGenerator/Controller/DelayGenerator-FringeScannerOffset.vi"/>
			<Item Name="AerotechGetTarget.vi" Type="VI" URL="../../Instruments/Aerotech/Clients/AerotechGetTarget.vi"/>
			<Item Name="DelayGeneratorSetOffset.vi" Type="VI" URL="../../Instruments/DelayGenerator/Clients/DelayGeneratorSetOffset.vi"/>
			<Item Name="FringeTrackerInfo.ctl" Type="VI" URL="../../Instruments/FringeTracker/Controls/FringeTrackerInfo.ctl"/>
			<Item Name="FringeTracker-GetState.vi" Type="VI" URL="../../Instruments/FringeTracker/Clients/FringeTracker-GetState.vi"/>
			<Item Name="FringeTrackerState.ctl" Type="VI" URL="../../Instruments/FringeTracker/Controls/FringeTrackerState.ctl"/>
			<Item Name="FringeTracker-Idle.vi" Type="VI" URL="../../Instruments/FringeTracker/Clients/FringeTracker-Idle.vi"/>
			<Item Name="FringTrackerCommand.ctl" Type="VI" URL="../../Instruments/FringeTracker/Controls/FringTrackerCommand.ctl"/>
			<Item Name="FringeTrackerData.ctl" Type="VI" URL="../../Instruments/FringeTracker/Controls/FringeTrackerData.ctl"/>
			<Item Name="FringeTracker-Scan.vi" Type="VI" URL="../../Instruments/FringeTracker/Clients/FringeTracker-Scan.vi"/>
			<Item Name="DelayGeneratorGetOffset.vi" Type="VI" URL="../../Instruments/DelayGenerator/Clients/DelayGeneratorGetOffset.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
