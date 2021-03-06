## Project Status

The HL2 Asset Importer plugin is still very much a work-in-progress and there is much to do before the game can be imported and is somewhat playable.
- Key
	- :heavy_check_mark: Full Support
	- :heavy_exclamation_mark: Partial Support / WIP
	- :x: No Support

### Assets

- :heavy_check_mark::heavy_exclamation_mark: Textures (.vtf) v<=7.5.3
	- :heavy_check_mark: Basic support
	- :heavy_check_mark: Normal maps
	- :heavy_check_mark: HDR
	- :x: Animated textures
	- :heavy_check_mark: Bulk Import
	
- :heavy_check_mark::heavy_exclamation_mark: Materials (.vmt)
	- Shaders
		- :heavy_check_mark: VertexLitGeneric
		- :heavy_check_mark: LightmappedGeneric
		- :heavy_check_mark: UnlitGeneric
		- :heavy_check_mark: UnlitTwoTexture
		- :heavy_check_mark: WorldVertexTransition
		- :heavy_check_mark: Refract
		- :heavy_check_mark: Decal
		- :heavy_exclamation_mark: Cable
		- :x: Subrect
		- :x: Anything else
	- :heavy_check_mark: Convert to PBR
	- :x: Proxies
	- :heavy_check_mark: Bulk Import

- :heavy_check_mark::heavy_exclamation_mark: Models (.mdl) v44-48
	- Static Props 
		- :heavy_check_mark: Basic Support
		- :heavy_check_mark: LODs
		- :heavy_check_mark: Collision
		- :heavy_check_mark: Materials
		- :heavy_exclamation_mark: Lightmap UVs
		- :heavy_check_mark: Skins
		- :heavy_check_mark: Model Groups
		- :x: Surface Prop (and other metadata)
	- Animated Models v44-48
		- :heavy_check_mark: Basic Support
		- :heavy_check_mark: LODs
		- :heavy_exclamation_mark: Collision
		- :heavy_check_mark: Materials
		- :heavy_check_mark: Skins
		- :heavy_check_mark: Model Groups
		- :heavy_check_mark: Skeleton and Rigging
		- :x: Morph Targets
		- :heavy_exclamation_mark: Sequences
		- :x: Automatic Blend Space Generation
		- :x: IK
		- :x: Surface Prop (and other metadata)
	- :heavy_check_mark: Bulk Import
	
- :heavy_check_mark::heavy_exclamation_mark: Maps (.bsp) v19-20
	- :heavy_check_mark: Brush Geometry
	- :x: Smoothing Groups
	- :heavy_exclamation_mark: Collision (see below)
	- :heavy_check_mark: Materials
	- :heavy_check_mark: Lightmap UVs
	- :heavy_exclamation_mark: Entities (see below)
	- :heavy_check_mark: Brush Entities
	- :heavy_exclamation_mark: 2D Skybox (functional, texture needs to be flipped on Y axis)
	- :heavy_exclamation_mark: 3D Skybox (functional, low quality?)
	- :heavy_check_mark: Displacements
	- :x: Visibility
	- :x: Bulk Import

- :x: Sounds
	- :x: Sound Entities (ambient_generic, env_soundscape)
	- :x: Sound Script Importing
	- :x: Soundscapes
	- :x: Bulk Import

- :x: Effects and Particles
	- :x: Particle System Importing

### Entities and Logic
	
- :heavy_check_mark::heavy_exclamation_mark: Entities (from .bsp)
	- :heavy_check_mark: Base Entity
	- :heavy_check_mark: KeyValues Parsing
	- :heavy_check_mark: I/O System
		- :heavy_check_mark: Firing Outputs and Receiving Inputs
		- :heavy_check_mark: Delayed Outputs
		- :heavy_check_mark: Outputs with Parameters
		- :heavy_check_mark::heavy_exclamation_mark: Special Targetnames
			- :heavy_check_mark: !activator
			- :heavy_check_mark: !caller
			- :heavy_check_mark: !self
			- :x: !player
			- :x: !pvsplayer
			- :x: !speechtarget
			- :x: !picker
	- :heavy_check_mark: Editor Icons
	- :heavy_check_mark::heavy_exclamation_mark: HL2 Entities
		- :heavy_check_mark: env_cubemap (see lighting section)
		- :heavy_exclamation_mark: func_brush
		- :heavy_exclamation_mark: func_illusionary
		- :heavy_check_mark: info_player_start
		- :heavy_check_mark: light (see lighting section)
		- :heavy_check_mark: light_environment (see lighting section)
		- :heavy_check_mark: light_spot (see lighting section)
		- :heavy_check_mark: logic_auto
		- :heavy_check_mark: logic_relay
		- :heavy_check_mark: logic_relay
		- :heavy_exclamation_mark: prop_dynamic
		- :heavy_exclamation_mark: prop_physics
		- :heavy_check_mark: prop_static
		- :heavy_check_mark: sky_camera
		- :heavy_check_mark: trigger_multiple
		- :heavy_check_mark: trigger_once
		- :heavy_check_mark: worldspawn
		- :x: Anything else

- :heavy_exclamation_mark: Player
	- :heavy_exclamation_mark: Basic Movement (use that one HL2 movement plugin somebody made?)
	- :x: Interaction
	- :x: Weapons

- :x: NPCs
	- :x: Basic NPC Entities
	- :x: NPC Animation
	- :x: NPC AI Logic

### Other

- :heavy_check_mark::heavy_exclamation_mark: Lighting
	- :heavy_exclamation_mark: Cubemaps - functional, but far too densely placed, need some way to remove unnecessary ones?
	- :heavy_exclamation_mark: Sun Light (light_environment - needs I/O support)
	- :heavy_check_mark: Ambient Light (light_environment ignored, uses skybox to emit light instead)
	- :heavy_exclamation_mark: Static Lights (light, light_spot - needs I/O support)
	- :x: Resolving Stationary Light Overlap (detect overlap and shrink attenuation radius until no longer overlapping?)
	- :x: Resolve Lighting Leaks (create extruded back-face geometry for whole map to block light?)

- :heavy_check_mark::heavy_exclamation_mark: Physics
	- :heavy_exclamation_mark: Map Collision (uses rendering geometry for collision testing, nodraw/playerclip/invisible aren't yet considered!)
	- :heavy_check_mark: Prop Collision
	- :x: Ragdolls
	- :x: Damage and Gibs
	
- :x: Misc
	- :x: UI
	- :x: Scripted Scenes

