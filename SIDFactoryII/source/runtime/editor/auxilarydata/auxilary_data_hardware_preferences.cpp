#include "auxilary_data_hardware_preferences.h"
#include "auxilary_data_utils.h"
#include "foundation/base/assert.h"
#include "utils/c64file.h"
#include "utils/config/configtypes.h"
#include "utils/configfile.h"
#include "utils/global.h"

using namespace Utility;
using namespace Utility::Config;

namespace Editor
{
	AuxilaryDataHardwarePreferences::AuxilaryDataHardwarePreferences()
		: AuxilaryData(Type::HardwarePreferences)
	{
		Reset();
	}


	void AuxilaryDataHardwarePreferences::Reset()
	{

		ConfigFile& config = Global::instance().GetConfig();
		int default_sid_model = GetSingleConfigurationValue<ConfigValueInt>(config, "Sound.Emulation.Default.Model", 8580);
		std::string default_region = GetSingleConfigurationValue<ConfigValueString>(config, "Sound.Emulation.Default.Region", std::string("PAL"));

		if (default_sid_model == 6581)
		{
			m_SIDModel = SIDModel::MOS6581;
		}
		else
		{
			m_SIDModel = SIDModel::MOS8580;
		}

		if (default_region == "NTSC")
		{
			m_Region = Region::NTSC;
		}
		else
		{
			m_Region = Region::PAL;
		}
	}


	const AuxilaryDataHardwarePreferences::SIDModel AuxilaryDataHardwarePreferences::GetSIDModel() const
	{
		return m_SIDModel;
	}


	void AuxilaryDataHardwarePreferences::SetSIDModel(const SIDModel inSIDModel)
	{
		m_SIDModel = inSIDModel;
	}


	const AuxilaryDataHardwarePreferences::Region AuxilaryDataHardwarePreferences::GetRegion() const
	{
		return m_Region;
	}


	void AuxilaryDataHardwarePreferences::SetRegion(const Region inRegion)
	{
		m_Region = inRegion;
	}


	std::vector<unsigned char> AuxilaryDataHardwarePreferences::GenerateSaveData() const
	{
		std::vector<unsigned char> output;

		AuxilaryDataUtils::SaveDataPushByte(output, m_SIDModel);
		AuxilaryDataUtils::SaveDataPushByte(output, m_Region);

		return output;
	}


	unsigned short AuxilaryDataHardwarePreferences::GetGeneratedFileVersion() const
	{
		return 1;
	}


	bool AuxilaryDataHardwarePreferences::RestoreFromSaveData(unsigned short inDataVersion, std::vector<unsigned char> inData)
	{
		auto it = inData.begin();

		m_SIDModel = static_cast<SIDModel>(AuxilaryDataUtils::LoadDataPullByte(it));
		m_Region = static_cast<Region>(AuxilaryDataUtils::LoadDataPullByte(it));

		return true;
	}
}
