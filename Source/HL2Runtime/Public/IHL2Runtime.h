#pragma once

#include "ModuleManager.h"
#include "VMTMaterial.h"
#include "Engine/Texture.h"

UENUM()
enum class EHL2BlendMode : uint8
{
	Opaque,
	AlphaTest,
	Translucent
};

class HL2RUNTIME_API IHL2Runtime : public IModuleInterface
{
public:

	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline IHL2Runtime& Get()
	{
		return FModuleManager::LoadModuleChecked<IHL2Runtime>("HL2Runtime");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("HL2Runtime");
	}

	virtual FString GetHL2BasePath() const = 0;
	virtual FString GetPluginBasePath() const = 0;
	
	virtual FString GetHL2TextureBasePath() const = 0;
	virtual FString GetHL2MaterialBasePath() const = 0;
	virtual FString GetHL2ShaderBasePath() const = 0;
	virtual FString GetHL2EntityBasePath() const = 0;

	virtual FName HL2TexturePathToAssetPath(const FString& hl2TexturePath) const = 0;
	virtual FName HL2MaterialPathToAssetPath(const FString& hl2MaterialPath) const = 0;
	virtual FName HL2ShaderPathToAssetPath(const FString& hl2ShaderPath, EHL2BlendMode blendMode = EHL2BlendMode::Opaque) const = 0;

	virtual UTexture* TryResolveHL2Texture(const FString& hl2TexturePath) const = 0;
	virtual UVMTMaterial* TryResolveHL2Material(const FString& hl2TexturePath) const = 0;
	virtual UMaterial* TryResolveHL2Shader(const FString& hl2ShaderPath, EHL2BlendMode blendMode = EHL2BlendMode::Opaque) const = 0;

	virtual void FindAllMaterialsThatReferenceTexture(const FString& hl2TexturePath, TArray<UVMTMaterial*>& out) const = 0;
	virtual void FindAllMaterialsThatReferenceTexture(FName assetPath, TArray<UVMTMaterial*>& out) const = 0;

};